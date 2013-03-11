//
//  user_management.h
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/11/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#ifndef AccessControl_user_management_h
#define AccessControl_user_management_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define USERS_DB "users_db"
#define BUFFER_SIZE 256

int add_user(char * username, char * password);

int check_access_control(char * username, char * password);

#endif
