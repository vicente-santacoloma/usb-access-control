//
//  client.h
//  AccessControl
//
//  Created by Vicente Santacoloma and Jesus Martinez.
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

/**
 * This function sets up the client parameters in order to 
 * establish new TCP connection with a remote server.
 * @return
 */
int tcp_connect();

/**
 * Verify the correctness of the command-line invocation of the program. 
 *
 * @param argc Number of arguments introduced.
 * @param argv Array containing the arguments values.
 * @param server_ip Server's IP address.
 * @param server_port_number Port number used by the server.
 * @return TRUE if the verification succeeds, FALSE otherwise.
 */
int client_load_parameters(int argc, const char * argv [], char ** server_ip,
                           int * server_port_number);

#endif
