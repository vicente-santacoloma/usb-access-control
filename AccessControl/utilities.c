//
//  utilities.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/10/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "utilities.h"

void error(const char * msg)
{
  perror(msg);
  exit(1);
}

int client_load_parameters(int argc, const char * argv [], char ** server_ip,
                           int * server_port_number)
{
    
  int b [2] = {FALSE, FALSE};
  int k = 1;
    
  if (argc != 5) {
    return FALSE;
  }
    
  while (k < argc) {
        
    if (argv[k][0] == '-') {
      
      switch (argv[k][1]) {
        case 's':
          if (b[0]) {
            return FALSE;
          }
          b[0] = TRUE;
          ++k;
          *server_ip = argv[k];
          break;
        case 'p':
          if (b[1]) {
            return FALSE;
          }
          b[1] = TRUE;
          ++k;
          *server_port_number = atoi(argv[k]);
          break;
        default:
          return FALSE;
      }
    } else {
      return FALSE;
    }
    ++k;
  }

  return TRUE;
}


int server_load_parameters(int argc, const char * argv [], int * port_number)
{
  if ((argc != 3) || (strcmp(argv[1],"-p") != 0)) {
    return FALSE;
  }
  *port_number = atoi(argv[2]);
    
  return TRUE;
}