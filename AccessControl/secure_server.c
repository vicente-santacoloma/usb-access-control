//
//  secure_server.c
//  AccessControl
//
//  Created by Vicente Santacoloma and Jesus Martinez.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "server.h"
#include "user_management.h"
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 256
#define USERNAME "Username:"
#define PASSWORD "Password:"
#define ACCESS_GRANTED "Access Granted"
#define ACCESS_DENIED  "Access Denied"
#define CERTIFICATE_FILE "certificate.crt"
#define KEY_FILE "privateKey.key"
#define FAIL -1

/**
 * This functions creates and initializes the SSL server's context. It
 * also loads the algorithms and error strings used by the SSL library.
 *
 * @return SSL_CTX object representing the current SSL context.
 */
SSL_CTX *initialize_context_server() {
  
  const SSL_METHOD *method;
  SSL_CTX *context;
 
  OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
  SSL_load_error_strings();   /* load all error messages */
  method = SSLv23_server_method();  /* create new server-method instance */
  context = SSL_CTX_new(method);   /* create new context from method */
  
  if (context == NULL)
  {
      ERR_print_errors_fp(stderr);
      abort();
  }
  
  SSL_CTX_set_verify(context, SSL_VERIFY_PEER, NULL);

  return context;
}


/**
 * Searchs and shows the client's certificates (if exists). In more detail, 
 * it provides the information contained in the Subject and Issuer fields.
 *
 * @param ssl SSL object containing the secure connection.
 */
void show_certificates(SSL * ssl) {
  
  X509 * certificate;
  char * line;
  
  certificate = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
  if (certificate != NULL)
  {
    printf("Server certificates:\n");
    line = X509_NAME_oneline(X509_get_subject_name(certificate), 0, 0);
    printf("Subject: %s\n", line);
    free(line);
    line = X509_NAME_oneline(X509_get_issuer_name(certificate), 0, 0);
    printf("Issuer: %s\n", line);
    free(line);
    X509_free(certificate);
  } else {
    printf("No certificates.\n");
  }
  

}

/**
 * Loads this server's certificate and private key into the SSL context.
 *
 * @param context Server's SSL context.
 * @param certificate_f Name or path where the certificate file is.
 * @param key_f Name or path where the key file is.
 */
void load_certificates(SSL_CTX* context, char* certificate_f, char* key_f) {
  
 /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(context, certificate_f, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(context, key_f, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(context) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}


/**
 * Performs the access control process by requesting authentication info
 * to the client and doing the subsequent data base check. Also informs client 
 * if access has been granted or denied, all through SSL connection.
 *
 * @param ssl SSL object containing the secure connection.
 */
void response_access_control(SSL* ssl) {
  
  char username[BUFFER_SIZE];
  char password[BUFFER_SIZE];
  int n;
  
  /* Buffer's initialization with zeros. */
  bzero(username, BUFFER_SIZE);
  bzero(password, BUFFER_SIZE);
  
  /* Asks client for the username. */
  n = SSL_write(ssl, USERNAME, strlen(USERNAME));
  if (n < 0) {
    error("ERROR writing to socket");
  }
  
  /* Retrieves client's response through secure socket. */
  n = SSL_read(ssl, username, BUFFER_SIZE);
  if (n < 0) {
    error("ERROR reading from socket");
  }
  username[strlen(username) - 1] = 0;
  

  /* Asks client for the password. */
  n = SSL_write(ssl, PASSWORD, strlen(PASSWORD));
  if (n < 0) {
    error("ERROR writing to socket");
  }
  
  /* Retrieves client's response through secure socket. */
  n = SSL_read(ssl, password, BUFFER_SIZE);
  if (n < 0) {
    error("ERROR reading from socket");
  }
  password[strlen(password) - 1] = 0;
  
  int access_control = check_access_control(username, password);
  printf("Access Control: %d\n", access_control);

  /* Informs client about its service request status. */
  if(access_control) {
    n = SSL_write(ssl, ACCESS_GRANTED, strlen(ACCESS_GRANTED));
    if (n < 0) {
      error("ERROR writing to socket");
    }
  } else {
    n = SSL_write(ssl, ACCESS_DENIED, strlen(ACCESS_DENIED));
    if (n < 0) {
      error("ERROR writing to socket");
    }
  }
  
}


/**
 * Starts the execution of the server's tasks: User's authentication and
 * posterior message exchange.
 */
void execute() {
  

  SSL_library_init();
  
  SSL_CTX *context;
  int sockfd, newsockfd, pid;
  sockfd = tcp_listen();

  socklen_t clilen;
  struct sockaddr_in cli_addr;
  clilen = sizeof(cli_addr);
  
  context = initialize_context_server();
  
  load_certificates(context, CERTIFICATE_FILE, KEY_FILE);

  while (1) {
    
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    
    if (newsockfd < 0) {
      error("ERROR on accept");
    }

    SSL *ssl;
    //BIO *sbio;

    /* Forks to handle concurrent requests. */
    pid = fork();

    if (pid < 0) {
      error("ERROR on fork");
    }

    if (pid == 0)  {
      close(sockfd);

      /* Connect the SSL socket */
      ssl = SSL_new(context);
      //sbio = BIO_new_socket(newsockfd, BIO_NOCLOSE);
      //SSL_set_bio(ssl, sbio, sbio);
      
      SSL_set_fd(ssl, newsockfd);
      
      /* do SSL-protocol accept */
      if (SSL_accept(ssl) == FAIL) {
        ERR_print_errors_fp(stderr);
      } else {
        //uncomment to show certificates
        //show_certificates(ssl);
        response_access_control(ssl);
      }
      
      close(newsockfd);
      SSL_CTX_free(context);
      SSL_free(ssl);
      exit(0);
    } else {
      close(newsockfd);
    }
  } /* end of while */
  close(sockfd);
  SSL_CTX_free(context);
}

/* The main routine starts the program execution. */
int main(int argc, const char * argv[]) {
  
  if (!server_load_parameters(argc, argv, &port_number)) {
    printf("Invalid Input Format\n");
    exit(1);
  }
  
  execute();
  
  return 0;
}
