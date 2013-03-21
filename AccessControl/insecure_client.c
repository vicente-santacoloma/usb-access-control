//
//  insecure_client.c
//  AccessControl
//
//  Created by Vicente Santacoloma and Jesus Martinez.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "client.h"

#define BUFFER_SIZE 256


/**
 * Performs the control access routine with the remote server.
 *
 * @param sockfd Socket filed descriptor that acts as communication channel.
 */
void request_access_control(int sockfd) {
  
  char buffer[BUFFER_SIZE];
  int k, n;
  
  /*The following instructions are executed twice: One for the Username
    and one for the Password.*/ 
  for (k = 0; k < 2; ++k) {
    bzero(buffer, BUFFER_SIZE);

    /* Gets server's request */
    n = read(sockfd, buffer, BUFFER_SIZE);
    if (n < 0) {
      error("ERROR reading from socket");
    }

    /* Prompts request to user. */
    printf("%s", buffer);
    
    bzero(buffer, BUFFER_SIZE);

    /* Gets user response. */
    fgets(buffer, BUFFER_SIZE, stdin);

    /* Sends user response to server. */
    n = write(sockfd, buffer, BUFFER_SIZE);
    if (n < 0) {
      error("ERROR writing to socket");
    }
  }
  
  bzero(buffer, BUFFER_SIZE);

  /* Gets service request status from the server. */
  n = read(sockfd, buffer, BUFFER_SIZE);
  if (n < 0) {
    error("ERROR reading from socket");
  }

  /*Prompts status to user.*/
  printf("%s\n", buffer);
  
}

void execute() {
  
  int sockfd;
  sockfd = tcp_connect();
  request_access_control(sockfd);
  close(sockfd);
  
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