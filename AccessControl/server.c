//
//  server.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/12/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "server.h"

int port_number;

int tcp_listen() {
  
  int sockfd, portno;
  struct sockaddr_in serv_addr;
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }
  
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = port_number;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  int val = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
             &val, sizeof(val));
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR on binding");
  }
  listen(sockfd, LISTEN_CONNECTIONS);
  return sockfd;
}

int server_load_parameters(int argc, const char * argv [], int *port_number) {
  
  if ((argc != 3) || (strcmp(argv[1],"-p") != 0)) {
    return FALSE;
  }

  *port_number = atoi(argv[2]);
  
  return TRUE;
}