//
//  client.h
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/12/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#ifndef AccessControl_client_h
#define AccessControl_client_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "common.h"

#define TRUE 1
#define FALSE 0

extern char * server_ip;

extern int server_port_number;

int tcp_connect();

int client_load_parameters(int argc, const char * argv [], char ** server_ip,
                           int * server_port_number);

#endif
