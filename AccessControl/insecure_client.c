//
//  insecure_client.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/10/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "utilities.h"

#define BUFFER_SIZE 256

char * server_ip;
int server_port_number;

void request_access_control(int sockfd)
{
  char buffer[BUFFER_SIZE];
  int k, n;
  
  for (k = 0; k < 2; ++k) {
    bzero(buffer, BUFFER_SIZE);
    n = read(sockfd, buffer, BUFFER_SIZE);
    if (n < 0) {
      error("ERROR reading from socket");
    }
    printf("\n%s", buffer);
    
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
  printf("\n%s", buffer);
  
}

void execute()
{
  int sockfd, portno;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  portno = server_port_number;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");
  server = gethostbyname(server_ip);
  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR connecting");
  }
  request_access_control(sockfd);
  close(sockfd);
  
}

int main(int argc, const char * argv[])
{
  
  if (!client_load_parameters(argc, argv, &server_ip, &server_port_number)) {
    printf("Invalid Input Format\n");
    exit(1);
  }
  
  execute();
  
  return 0;
}