//
//  secure_client.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/10/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <resolv.h>
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/x509.h"
#include "openssl/pem.h"
#include "openssl/crypto.h"

#include "client.h"

#define BUFFER_SIZE 256
#define REQUIRE_SERVER_AUTH 0

/* Print SSL errors and exit*/
int berr_exit(char *string) {
  fprintf(stderr,"%s\n",string);
  //BIO_printf(bio_err,"%s\n",string);
  //ERR_print_errors(bio_err);
  exit(0);
}

/* A simple error and exit routine*/
int err_exit(char *string) {
  fprintf(stderr,"%s\n",string);
  exit(0);
}

SSL_CTX * initialize_context_client() {

  const SSL_METHOD *method;
  SSL_CTX *context;

  OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
  SSL_load_error_strings();   /* Bring in and register error messages */
  method = SSLv23_client_method();  /* Create new client-method instance */
  context = SSL_CTX_new(method);   /* Create new context */
  if ( context == NULL ) {
    ERR_print_errors_fp(stderr);
    abort();
  }
  return context;
}

void verify_certificate(SSL * ssl, char * host) {
  
  X509 * certificate;
  char subject_name [256];
  
  if (!(certificate = SSL_get_peer_certificate(ssl)) || !host) {
    berr_exit("Certificate hasn't been provided");
  } else {
    
    if (SSL_get_verify_result(ssl) != X509_V_OK) {
      berr_exit("Certificate doesn't verify");
    }
    
    /*Check the common name*/
    X509_NAME_get_text_by_NID(X509_get_subject_name(certificate),
                              NID_commonName, subject_name, 256);
    if(strcasecmp(subject_name, host)) {
      err_exit("Common name doesn't match host name");
    }
  }

}

void request_access_control(SSL * ssl) {
  
  char buffer[BUFFER_SIZE];
  int k, n;
  
  for (k = 0; k < 2; ++k) {
    bzero(buffer, BUFFER_SIZE);
    n = SSL_read(ssl, buffer, BUFFER_SIZE);
    if (n < 0) {
      error("ERROR reading from socket");
    }
    printf("%s", buffer);
    
    bzero(buffer, BUFFER_SIZE);
    fgets(buffer, BUFFER_SIZE, stdin);
    n = SSL_write(ssl, buffer, BUFFER_SIZE);
    if (n < 0) {
      error("ERROR writing to socket");
    }
  }
  
  bzero(buffer, BUFFER_SIZE);
  n = SSL_read(ssl, buffer, BUFFER_SIZE);
  if (n < 0) {
    error("ERROR reading from socket");
  }
  printf("%s", buffer);
  
}

void execute() {
  
  SSL_library_init();
  
  SSL_CTX * context;
  BIO *sbio;
  SSL * ssl;
  int sockfd;
  
  /* Build our SSL context*/
  context = initialize_context_client();
  
  /* Connect the TCP socket*/
  sockfd = tcp_connect();
  
  /* Connect the SSL socket */
  //SSL_set_fd(ssl, sockfd);
  
  /* Connect the SSL socket */
  ssl = SSL_new(context);
  sbio = BIO_new_socket(sockfd, BIO_NOCLOSE);
  SSL_set_bio(ssl, sbio, sbio);
  
  if(SSL_connect(ssl) <= 0) {
    berr_exit("SSL connect error");
  }
  
  
  if(REQUIRE_SERVER_AUTH) {
    verify_certificate(ssl, server_ip);
  }
  
  request_access_control(ssl);
  
  close(sockfd);
  
  /* Shutdown the socket */
  SSL_CTX_free(context);
  

}

int main(int argc, const char * argv[]) {
  
  if (!client_load_parameters(argc, argv, &server_ip, &server_port_number)) {
    printf("Invalid Input Format\n");
    exit(1);
  }
  
  execute();
  free(server_ip);
  
  return 0;
}