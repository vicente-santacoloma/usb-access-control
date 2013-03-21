//
//  user_management.c
//  AccessControl
//
//  Created by Vicente Santacoloma and Jesus Martinez.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "user_management.h"

char hash_password [SHA512_DIGEST_LENGTH];

void sha512(char * data) {
  
  unsigned char hash [SHA512_DIGEST_LENGTH];
  
  SHA512((unsigned char *) data, strlen(data), hash);
  
  int i;
  for(i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
    sprintf(hash_password + (i * 2), "%02x", hash[i]);
  }
  
}

int add_user(char * username, char * password) {
  
  FILE *fp;
  
  /* open the file */
  fp = fopen(USERS_DB, "a");
  if (fp == NULL) {
    printf("I couldn't open %s for appending.\n", USERS_DB);
    exit(0);
  }
  
  if (HASH) {
    sha512(password);
    /* write to the file */
    fprintf(fp, "%s %s\n", username, hash_password);
  } else {
    fprintf(fp, "%s %s\n", username, password);
  }
  
  /* close the file */
  fclose(fp);
  
  return TRUE;
}

int check_access_control(char * username, char * password) {
  
  FILE * fp;
  char aux_username [BUFFER_SIZE];
  char aux_password [BUFFER_SIZE];
  
  if ((fp = fopen(USERS_DB, "r")) == NULL) {
    printf("I couldn't open %s for reading.\n", USERS_DB);
    exit(0);
  }
  
  while (!feof(fp)) {
    
    fscanf(fp, "%s %s\n", aux_username, aux_password);
    
    //printf("%s\n%s\n\n", sha512(password), aux_password);
    
    if (strcmp(username, aux_username) == 0) {
      
      int password_validate;
      
      if (HASH) {
        sha512(password);
        password_validate = strcmp(hash_password, aux_password);
      } else {
        password_validate = strcmp(password, aux_password);
      }
      
      if (password_validate == 0) {
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
