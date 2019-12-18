#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* zArgv0; } ;

/* Variables and functions */
 TYPE_1__ g ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void showHelp(void){
  printf("Usage: %s [options] DB1 DB2\n", g.zArgv0);
  printf(
"Output SQL text that would transform DB1 into DB2.\n"
"Options:\n"
"  --changeset FILE      Write a CHANGESET into FILE\n"
"  -L|--lib LIBRARY      Load an SQLite extension library\n"
"  --primarykey          Use schema-defined PRIMARY KEYs\n"
"  --rbu                 Output SQL to create/populate RBU table(s)\n"
"  --schema              Show only differences in the schema\n"
"  --summary             Show only a summary of the differences\n"
"  --table TAB           Show only differences in table TAB\n"
"  --transaction         Show SQL output inside a transaction\n"
"  --vtab                Handle fts3, fts4, fts5 and rtree tables\n"
  );
}