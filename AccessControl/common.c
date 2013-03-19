//
//  common.c
//  AccessControl
//
//  Created by Vicente Santacoloma and Jesus Martinez.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include "common.h"

void error(const char * msg) {
  perror(msg);
  exit(1);
}