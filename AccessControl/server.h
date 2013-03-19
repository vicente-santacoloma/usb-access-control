//
//  server.h
//  AccessControl
//
//  Created by Vicente Santacoloma and Jesus Martinez.
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

/** 
 * This function sets up the server parameters in order to attend new TCP
 * connections.
 *
 *@return The socket file descriptor which is able to receive new connections. 
 */
int tcp_listen();


/**
 * Verify the correctness of the command-line invocation of the program. 
 *
 * @param argc Number of arguments introduced.
 * @param argv Array containing the arguments values.
 * @param port_number Port number used by the server.
 * @return TRUE if the verification succeeds, FALSE otherwise.
 */
int server_load_parameters(int argc, const char * argv [], int * port_number);

#endif
