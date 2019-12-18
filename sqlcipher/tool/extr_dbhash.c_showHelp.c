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
  printf("Usage: %s [options] FILE ...\n", g.zArgv0);
  printf(
"Compute a SHA1 hash on the content of database FILE.  System tables such as\n"
"sqlite_stat1, sqlite_stat4, and sqlite_sequence are omitted from the hash.\n"
"Options:\n"
"   --debug N           Set debugging flags to N (experts only)\n"
"   --like PATTERN      Only hash tables whose name is LIKE the pattern\n"
"   --schema-only       Only hash the schema - omit table content\n"
"   --without-schema    Only hash table content - omit the schema\n"
  );
}