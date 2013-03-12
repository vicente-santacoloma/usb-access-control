//
//  insecure_client.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/10/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "client.h"

#define BUFFER_SIZE 256

void request_access_control(int sockfd) {
  
  char buffer[BUFFER_SIZE];
  int k, n;
  
  for (k = 0; k < 2; ++k) {
    bzero(buffer, BUFFER_SIZE);
    n = read(sockfd, buffer, BUFFER_SIZE);
    if (n < 0) {
      error("ERROR reading from socket");
    }
    printf("%s", buffer);
    
    bzero(buffer, BUFFER_SIZE);
    fgets(buffer, BUFFER_SIZE, stdin);
    n = write(sockfd, buffer, BUFFER_SIZE);
    if (n < 0) {
      error("ERROR writing to socket");
    }
  }
  
  bzero(buffer, BUFFER_SIZE);
  n = read(sockfd, buffer, BUFFER_SIZE);
  if (n < 0) {
    error("ERROR reading from socket");
  }
  printf("%s", buffer);
  
}

void execute() {
  
  int sockfd;
  sockfd = tcp_connect();
  request_access_control(sockfd);
  close(sockfd);
  
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