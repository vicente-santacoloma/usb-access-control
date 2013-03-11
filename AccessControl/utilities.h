//
//  utilities.h
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/11/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#ifndef AccessControl_utilities_h
#define AccessControl_utilities_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void error(const char *msg);

int client_load_parameters(int argc, const char * argv [], char ** server_ip,
                           int * server_port_number);

int server_load_parameters(int argc, const char * argv [], int * port_number);

#endif
