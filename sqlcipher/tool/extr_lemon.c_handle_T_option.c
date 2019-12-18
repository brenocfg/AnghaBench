#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ lemonStrlen (char*) ; 
 int /*<<< orphan*/  lemon_strcpy (char*,char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memory_error () ; 
 char* user_templatename ; 

__attribute__((used)) static void handle_T_option(char *z){
  user_templatename = (char *) malloc( lemonStrlen(z)+1 );
  if( user_templatename==0 ){
    memory_error();
  }
  lemon_strcpy(user_templatename, z);
}