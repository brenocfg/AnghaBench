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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void showHelp(const char *zArgv0){
  printf("Usage: %s ARGS...\n", zArgv0);
  printf("Arguments:\n"
    "  NUM    Convert NUM from integer to LogEst and push onto the stack\n"
    " ^NUM    Interpret NUM as a LogEst and push onto stack\n"
    "  x      Multiple the top two elements of the stack\n"
    "  +      Add the top two elements of the stack\n"
    "  dup    Dupliate the top element on the stack\n"
    "  inv    Take the reciprocal of the top of stack.  N = 1/N.\n"
    "  log    Find the LogEst of the number on top of stack\n"
    "  nlogn  Compute NlogN where N is the top of stack\n"
  );
  exit(1);
}