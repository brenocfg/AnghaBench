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
 char* sqlite3_libversion () ; 
 char* sqlite3_sourceid () ; 

__attribute__((used)) static void usage(const char *argv0){
  printf("Usage: %s [OPTIONS] DATABASE LOG\n\n", argv0);
  printf(
    "DATABASE is an SQLite database against which various statements\n"
    "have been run.  The SQL text is stored in LOG.  LOG is an SQLite\n"
    "database with this schema:\n"
    "\n"
    "    CREATE TABLE sqllog(sql TEXT);\n"
    "\n"
    "This utility program analyzes statements contained in LOG and prints\n"
    "a report showing how many times each index in DATABASE is used by the\n"
    "statements in LOG.\n"
    "\n"
    "DATABASE only needs to contain the schema used by the statements in\n"
    "LOG. The content can be removed from DATABASE.\n"
  );
  printf(
    "\nOPTIONS:\n\n"
    "    --progress N   Show a progress message after every N input rows\n"
    "    -q             Omit error message when parsing log entries\n"
    "    --using NAME   Print SQL statements that use index NAME\n"
  );
  printf("\nAnalysis will be done by SQLite version %s dated %.20s\n"
         "checkin number %.40s. Different versions\n"
         "of SQLite might use different indexes.\n",
         sqlite3_libversion(), sqlite3_sourceid(), sqlite3_sourceid()+21);
  exit(1);
}