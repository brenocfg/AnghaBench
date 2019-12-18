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
 int tdb_open (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  testSetError (int) ; 

TestDb *testOpen(const char *zSystem, int bClear, int *pRc){
  TestDb *pDb = 0;
  if( *pRc==0 ){
    int rc;
    rc = tdb_open(zSystem, 0, bClear, &pDb);
    if( rc!=0 ){
      testSetError(rc);
      *pRc = rc;
    }
  }
  return pDb;
}