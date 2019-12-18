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
typedef  int /*<<< orphan*/  TestDb ;

/* Variables and functions */
 char* tdb_default_db (char const*) ; 
 char* tdb_library_name (int /*<<< orphan*/ *) ; 
 int tdb_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testCopyLsmdb (char const*,char const*) ; 

void testReopenRecover(TestDb **ppDb, int *pRc){
  if( *pRc==0 ){
    const char *zLib = tdb_library_name(*ppDb);
    const char *zDflt = tdb_default_db(zLib);
    testCopyLsmdb(zDflt, "bak.db");
    testClose(ppDb);
    testCopyLsmdb("bak.db", zDflt);
    *pRc = tdb_open(zLib, 0, 0, ppDb);
  }
}