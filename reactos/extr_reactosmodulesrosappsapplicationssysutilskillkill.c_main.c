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
 int /*<<< orphan*/  DBG_UNREFERENCED_LOCAL_VARIABLE (char) ; 
 char ExecuteKill (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
  char tail;
  DBG_UNREFERENCED_LOCAL_VARIABLE(tail);

  if (argc < 2)
  {
      fprintf( stderr, "Usage: %s PID (Process ID) \n", argv[0] );
      return 1;
  }
  tail = ExecuteKill(argv[1]);
  return 0;
}