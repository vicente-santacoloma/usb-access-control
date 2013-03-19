//
//  insecure_server.c
//  AccessControl
//
//  Created by Vicente Santacoloma and Jesus Martinez.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "server.h"
#include "user_management.h"

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 256
#define USERNAME "Username:"
#define PASSWORD "Password:"
#define ACCESS_GRANTED "Access Granted"
#define ACCESS_DENIED  "Access Denied"

/**
 * Performs the access control process by requesting authentication info
 * to the client and doing the subsequent data base check. Also informs client 
 * if access has been granted or denied, all through an ordinary TCP connection.
 *
 * @param newsockfd Socket file descriptor that acts as a communication channel.
 */
void response_access_control(int newsockfd) {
  
  char username [BUFFER_SIZE];
  char password [BUFFER_SIZE];
  int n;
   
  /* Buffer's initialization with zeros. */
  bzero(username, BUFFER_SIZE);
  bzero(password, BUFFER_SIZE);

  /* Asks client for the username. */
  n = write(newsockfd, USERNAME, strlen(USERNAME));
  if (n < 0) {
    error("ERROR writing to socket");
  }
  
  /* Retrieves client's response through socket. */
  n = read(newsockfd, username, BUFFER_SIZE);
  if (n < 0) {
    error("ERROR reading from socket");
  }
  
  username[strlen(username) - 1] = 0;
  
  /* Asks client for the password. */
  n = write(newsockfd, PASSWORD, strlen(PASSWORD));
  if (n < 0) {
    error("ERROR writing to socket");
  }
  
  /* Retrieves client's response through socket. */
  n = read(newsockfd, password, BUFFER_SIZE);
  if (n < 0) {
    error("ERROR reading from socket");
  }
  password[strlen(password) - 1] = 0;
  
  int access_control = check_access_control(username, password);
  printf("Access Control: %d\n", access_control);

  /* Informs client about its service request status. */
  if(access_control) {
    n = write(newsockfd, ACCESS_GRANTED, strlen(ACCESS_GRANTED));
    if (n < 0) {
      error("ERROR writing to socket");
    }
  } else {
    n = write(newsockfd, ACCESS_DENIED, strlen(ACCESS_DENIED));
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
  
  int sockfd, newsockfd, pid;
  sockfd = tcp_listen();
  socklen_t clilen;
  struct sockaddr_in cli_addr;
  clilen = sizeof(cli_addr);
  
  while (1) {
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    
    if (newsockfd < 0) {
      error("ERROR on accept");
    }
    pid = fork();
    if (pid < 0) {
      error("ERROR on fork");
    }
    if (pid == 0)  {
      close(sockfd);
      response_access_control(newsockfd);
      close(newsockfd);
      exit(0);
    } else {
      close(newsockfd);
    }
  } /* end of while */
  close(sockfd);

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