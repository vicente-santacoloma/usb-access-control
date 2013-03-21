//
//  user_management.h
//  AccessControl
//
//  Created by Vicente Santacoloma and Jesus Martinez.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserve/Users/vicente/Documents/Projects/AccessControl/AccessControl/main.cd.
//

#ifndef AccessControl_user_management_h
#define AccessControl_user_management_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/sha.h"
#include <openssl/evp.h>

#define TRUE 1
#define FALSE 0
#define USERS_DB "users_db"
#define BUFFER_SIZE 256
#define HASH 1

/**
 * Calculates the hash value of a string.
 *
 * @param date The data to be calculated its hash
 */
void sha512(char * data);

/**
 * Adds a new user to the server's data base file containing all the users.
 *
 * @param username Username of the new user.
 * @param password Secret password of the new user.
 * @return TRUE if the operation succeeds, FALSE otherwise.
 */
int add_user(char * username, char * password);


/**
 * Checks the authenticity of the user who's trying to connect to the server.
 *
 * @param username Username of the user.
 * @param password Password of the user.
 * @return TRUE if the user has been authenticated, FALSE if not.
 *
 */
int check_access_control(char * username, char * password);

#endif