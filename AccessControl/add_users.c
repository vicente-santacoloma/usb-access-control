//
//  add_users.c
//  AccessControl
//
//  Created by Vicente Santacoloma on 3/21/13.
//  Copyright (c) 2013 Vicente Santacoloma. All rights reserved.
//

#include <stdio.h>

#include "user_management.h"

int main(int argc, const char * argv[]) {
  
  add_user("user1", "user1");
  add_user("user2", "user2");
  add_user("user3", "user3");
  add_user("user4", "user4");
  add_user("user5", "user5");
  add_user("user6", "user6");
  add_user("user7", "user7");
  add_user("user8", "user8");
  add_user("user9", "user9");
  add_user("user10", "user10");
  //printf("Check: %d", check_access_control("user10", "user10"));
  
  return 0;
}