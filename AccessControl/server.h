//
//  server.h
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/12/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#ifndef AccessControl_server_h
#define AccessControl_server_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "common.h"

#define TRUE 1
#define FALSE 0
#define LISTEN_CONNECTIONS 10

extern int port_number;

int tcp_listen();

int server_load_parameters(int argc, const char * argv [], int * port_number);

#endif
