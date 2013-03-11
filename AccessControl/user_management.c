//
//  user_management.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/11/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define USERS_DB "users_db"
#define BUFFER_SIZE 256

int add_user(char * username, char * password)
{
  FILE *fp;
  
  /* open the file */
  fp = fopen(USERS_DB, "a");
  if (fp == NULL) {
    printf("I couldn't open %s for appending.\n", USERS_DB);
    exit(0);
  }
  
  /* write to the file */
  fprintf(fp, "%s %s\n", username, password);
  
  /* close the file */
  fclose(fp);
  
  return TRUE;
}

int check_access_control(char * username, char * password)
{
  FILE * fp;
  char aux_username [BUFFER_SIZE];
  char aux_password [BUFFER_SIZE];
  
  if ((fp = fopen(USERS_DB, "r")) == NULL) {
    printf("I couldn't open %s for reading.\n", USERS_DB);
    exit(0);
  }
  
  while (!feof(fp)) {
    
    fscanf(fp, "%s %s\n", aux_username, aux_password);
    
    if (strcmp(username, aux_username) == 0) {
      if (strcmp(password, aux_password) == 0) {
        fclose(fp);
        return TRUE;
      } else {
        fclose(fp);
        return FALSE;
      }
    }
    
  }
  fclose(fp);
  return FALSE;
}

int main(int argc, const char * argv[])
{
  
  
  return 0;
}