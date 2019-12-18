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
typedef  int /*<<< orphan*/  lsm_db ;
typedef  int /*<<< orphan*/  OomTest ;

/* Variables and functions */
 int LSM_OK ; 
 int lsm_insert (int /*<<< orphan*/ *,void*,int,void*,int) ; 
 int /*<<< orphan*/  testOomAssertRc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void testOomWrite(
  OomTest *pOom,
  lsm_db *pDb,
  void *pKey, int nKey,
  void *pVal, int nVal,
  int *pRc
){
  testOomAssertRc(pOom, *pRc);
  if( *pRc==LSM_OK ){
    int rc;

    rc = lsm_insert(pDb, pKey, nKey, pVal, nVal);
    testOomAssertRc(pOom, rc);

    *pRc = rc;
  }
}