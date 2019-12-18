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
 int tdb_delete_range (int /*<<< orphan*/ *,void*,int,void*,int) ; 
 int /*<<< orphan*/  testSetError (int) ; 

void testDeleteRange(
  TestDb *pDb,                    /* Database handle */
  void *pKey1, int nKey1,
  void *pKey2, int nKey2,
  int *pRc                        /* IN/OUT: Error code */
){
  if( *pRc==0 ){
    int rc;
    *pRc = rc = tdb_delete_range(pDb, pKey1, nKey1, pKey2, nKey2);
    testSetError(rc);
  }
}