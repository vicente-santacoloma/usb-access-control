//
//  secure_client.c
//  AccessControl
//
//  Created by Vicente Santacoloma and Jesus Martinez.
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
#define REQUIRE_SERVER_AUTH 1

/** 
 * Print SSL errors and exit
 * @param string Error description.
 */
int berr_exit(char *string) {
  fprintf(stderr,"%s\n",string);
  //BIO_printf(bio_err,"%s\n",string);
  //ERR_print_errors(bio_err);
  exit(0);
}

/** 
 * A simple error and exit routine
 * @param string Error description.
 */
int err_exit(char *string) {
  fprintf(stderr,"%s\n",string);
  exit(0);
}

/**
 * This functions creates and initializes the SSL client's context. It
 * also loads the algorithms and error strings used by the SSL library.
 *
 * @return SSL_CTX object representing the current SSL context.
 */
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


/**
 * Requests and shows the server's certificate. In more detail, 
 * it provides the information contained in the Subject and Issuer fields.
 *
 * @param ssl SSL object containing the secure connection.
 */
void show_certificate(SSL* ssl) {
  
  X509 *certificate;
  char *line;
  
  certificate = SSL_get_peer_certificate(ssl); /* get the server's certificate */
  if (certificate != NULL)
  {
    printf("Server certificates:\n");
    line = X509_NAME_oneline(X509_get_subject_name(certificate), 0, 0);
    printf("Subject: %s\n", line);
    free(line);       /* free the malloc'ed string */
    line = X509_NAME_oneline(X509_get_issuer_name(certificate), 0, 0);
    printf("Issuer: %s\n", line);
    free(line);       /* free the malloc'ed string */
    X509_free(certificate);     /* free the malloc'ed certificate copy */
  } else {
    printf("No certificates.\n");
  }
}

/**
 * Verifies the information contained in the server's certificate.
 *
 * @param ssl SSL object containing the secure connection.
 * @param host Server's hostname.
 */
void verify_certificate(SSL * ssl, char * host) {
  
  X509 * certificate;
  char subject_name [256];
  
  /* Gets server's certificate */
  if (!(certificate = SSL_get_peer_certificate(ssl)) || !host) {
    berr_exit("Certificate hasn't been provided");
  } else {
    
    //long result = SSL_get_verify_result(ssl);
    //printf("result: %ld", result);

    /*Given that the server signs its own certificate, we are unable to verify
      the correctness of it comparing the value retrieved by the SSL_get_verify_result()
      function with X509_V_0K. Instead, the best we can do is verify that the certified
      is indeed self signed by the server and no one else.
      */
    if (SSL_get_verify_result(ssl) != X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT) {
      berr_exit("Certificate doesn't verify");
    }
    
    /*Check the common name*/
    /*
    X509_NAME_get_text_by_NID(X509_get_subject_name(certificate),
                              NID_commonName, subject_name, 256);
    //printf("subject_name: %s" , subject_name);
    if(strcasecmp(subject_name, host)) {
      err_exit("Common name doesn't match host name");
    }
    */
  }

}


/**
 * Performs the control access routine with the remote server.
 *
 * @param ssl SSL object containing the secure connection.
 */
void request_access_control(SSL * ssl) {
  
  char buffer[BUFFER_SIZE];
  int k, n;
  
  /*The following instructions are executed twice: One for the Username
    and one for the Password.*/ 
  for (k = 0; k < 2; ++k) {
    bzero(buffer, BUFFER_SIZE);

    /* Gets server's request */
    n = SSL_read(ssl, buffer, BUFFER_SIZE);
    if (n < 0) {
      error("ERROR reading from socket");
    }

    /* Prompts request to user. */
    printf("%s", buffer);
    
    bzero(buffer, BUFFER_SIZE);
    
    /* Gets user response. */
    fgets(buffer, BUFFER_SIZE, stdin);

    /* Sends user response to server. */
    n = SSL_write(ssl, buffer, BUFFER_SIZE);
    if (n < 0) {
      error("ERROR writing to socket");
    }
  }
  
  bzero(buffer, BUFFER_SIZE);
  /* Gets service request status from the server. */
  n = SSL_read(ssl, buffer, BUFFER_SIZE);
  if (n < 0) {
    error("ERROR reading from socket");
  }
  /*Prompts status to user.*/
  printf("%s\n", buffer);
  
}

void execute() {
  
  SSL_library_init();
  
  SSL_CTX * context;
  //BIO *sbio;
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
  //sbio = BIO_new_socket(sockfd, BIO_NOCLOSE);
  //SSL_set_bio(ssl, sbio, sbio);
  
  SSL_set_fd(ssl, sockfd);
  
  if(SSL_connect(ssl) <= 0) {
    berr_exit("SSL connect error");
  }
  
  //uncomment to show certificates
  //show_certificate(ssl); 
  
  if(REQUIRE_SERVER_AUTH) {
    verify_certificate(ssl, server_ip);
  }
  
  request_access_control(ssl);
  
  close(sockfd);
  
  /* Shutdown the socket */
  SSL_CTX_free(context);
  

}

/* The main routine starts the program execution. */
int main(int argc, const char * argv[]) {
  
  if (!client_load_parameters(argc, argv, &server_ip, &server_port_number)) {
    printf("Invalid Input Format\n");
    exit(1);
  }
  
  execute();
  free(server_ip);
  
  return 0;
}