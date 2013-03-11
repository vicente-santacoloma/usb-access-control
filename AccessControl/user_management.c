//
//  user_management.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/11/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "user_management.h"

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

/*
int main(int argc, const char * argv[])
{
  add_user("user1", "user1");
  add_user("user2", "user2");
  add_user("user3", "user3");
  add_user("user4", "user4");
  add_user("user5", "user5");
  printf("Check: %d", check_access_control("user1", "user1"));
  
  return 0;
}*/
