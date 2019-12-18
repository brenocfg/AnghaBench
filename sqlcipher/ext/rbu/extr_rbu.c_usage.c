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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

void usage(const char *zArgv0){
  fprintf(stderr, 
"Usage: %s ?OPTIONS? TARGET-DB RBU-DB\n"
"\n"
"Where options are:\n"
"\n"
"    -step NSTEP\n"
"    -statstep NSTATSTEP\n"
"    -vacuum\n"
"    -presql SQL\n"
"\n"
"  If the -vacuum switch is not present, argument RBU-DB must be an RBU\n"
"  database containing an update suitable for target database TARGET-DB.\n"
"  Or, if -vacuum is specified, then TARGET-DB is a database to vacuum using\n"
"  RBU, and RBU-DB is used as the state database for the vacuum (refer to\n"
"  API documentation for details).\n"
"\n"
"  If NSTEP is set to less than or equal to zero (the default value), this \n"
"  program attempts to perform the entire update or vacuum operation before\n"
"  exiting\n"
"\n"
"  If NSTEP is greater than zero, then a maximum of NSTEP calls are made\n"
"  to sqlite3rbu_step(). If the RBU update has not been completely applied\n"
"  after the NSTEP'th call is made, the state is saved in the database RBU-DB\n"
"  and the program exits. Subsequent invocations of this (or any other RBU)\n"
"  application will use this state to resume applying the RBU update to the\n"
"  target db.\n"
"\n"
, zArgv0);
  exit(1);
}