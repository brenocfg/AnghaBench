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
 scalar_t__ lsm_memcmp (void*,void*,int) ; 
 int tdb_fetch (int /*<<< orphan*/ *,void*,int,void**,int*) ; 
 int /*<<< orphan*/  testSetError (int) ; 

void testFetch(
  TestDb *pDb,                    /* Database handle */
  void *pKey, int nKey,           /* Key to query database for */
  void *pVal, int nVal,           /* Expected value */
  int *pRc                        /* IN/OUT: Error code */
){
  if( *pRc==0 ){
    void *pDbVal;
    int nDbVal;
    int rc;

    static int nCall = 0; nCall++;

    rc = tdb_fetch(pDb, pKey, nKey, &pDbVal, &nDbVal);
    testSetError(rc);
    if( rc==0 && (nVal!=nDbVal || (nVal>0 && lsm_memcmp(pVal, pDbVal, nVal))) ){
      testSetError(1);
    }
  }
}