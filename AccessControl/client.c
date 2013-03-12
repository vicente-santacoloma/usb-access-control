//
//  client.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/12/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "client.h"

char * server_ip;

int server_port_number;

int tcp_connect() {
  
  int sockfd, portno;
  struct sockaddr_in serv_addr;
  struct hostent * server;
  
  portno = server_port_number;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }
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
  return sockfd;
}

int client_load_parameters(int argc, const char * argv [], char ** server_ip,
                           int * server_port_number) {
  
  int b [2] = {FALSE, FALSE};
  int k = 1;
  
  if (argc != 5) {
    return FALSE;
  }
  
  while (k < argc) {
    
    if (argv[k][0] == '-') {
      
      switch (argv[k][1]) {
        case 's':
          if (b[0]) {
            return FALSE;
          }
          b[0] = TRUE;
          ++k;
          *server_ip = (char *) malloc (strlen(argv[k]));
          if(*server_ip == NULL) {
            perror("malloc");
            exit(1);
          }
          strcpy(*server_ip, argv[k]);
          break;
        case 'p':
          if (b[1]) {
            return FALSE;
          }
          b[1] = TRUE;
          ++k;
          *server_port_number = atoi(argv[k]);
          break;
        default:
          return FALSE;
      }
    } else {
      return FALSE;
    }
    ++k;
  }
  
  return TRUE;
}