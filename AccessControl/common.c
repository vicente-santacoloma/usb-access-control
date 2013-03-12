//
//  common.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/12/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "common.h"

void error(const char * msg) {
  perror(msg);
  exit(1);
}