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
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void showHelp(const char *zArgv0){
  printf("\n"
"Usage: %s SWITCHES... DB\n"
"\n"
"  This program opens the database named on the command line and attempts to\n"
"  create an FTS table named \"fts\" with a single column. If successful, it\n"
"  recursively traverses the directory named by the -dir option and inserts\n"
"  the contents of each file into the fts table. All files are assumed to\n"
"  contain UTF-8 text.\n"
"\n"
"Switches are:\n"
"  -fts [345]       FTS version to use (default=5)\n"
"  -idx [01]        Create a mapping from filename to rowid (default=0)\n"
"  -dir <path>      Root of directory tree to load data from (default=.)\n"
"  -trans <integer> Number of inserts per transaction (default=1)\n"
, zArgv0
);
  exit(1);
}