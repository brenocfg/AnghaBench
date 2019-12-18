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
typedef  int /*<<< orphan*/  lsm_cursor ;
typedef  int /*<<< orphan*/  OomTest ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  lsm_csr_close (int /*<<< orphan*/ *) ; 
 int lsm_csr_key (int /*<<< orphan*/ *,void const**,int*) ; 
 int lsm_csr_open (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int lsm_csr_seek (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int lsm_csr_valid (int /*<<< orphan*/ *) ; 
 int lsm_csr_value (int /*<<< orphan*/ *,void const**,int*) ; 
 scalar_t__ memcmp (void*,void const*,int) ; 
 int /*<<< orphan*/  testOomAssert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testOomAssertRc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void testOomFetch(
  OomTest *pOom,
  lsm_db *pDb,
  void *pKey, int nKey,
  void *pVal, int nVal,
  int *pRc
){
  testOomAssertRc(pOom, *pRc);
  if( *pRc==LSM_OK ){
    lsm_cursor *pCsr;
    int rc;

    rc = lsm_csr_open(pDb, &pCsr);
    if( rc==LSM_OK ) rc = lsm_csr_seek(pCsr, pKey, nKey, 0);
    testOomAssertRc(pOom, rc);

    if( rc==LSM_OK ){
      const void *p; int n;
      testOomAssert(pOom, lsm_csr_valid(pCsr));

      rc = lsm_csr_key(pCsr, &p, &n);
      testOomAssertRc(pOom, rc);
      testOomAssert(pOom, rc!=LSM_OK || (n==nKey && memcmp(pKey, p, nKey)==0) );
    }

    if( rc==LSM_OK ){
      const void *p; int n;
      testOomAssert(pOom, lsm_csr_valid(pCsr));

      rc = lsm_csr_value(pCsr, &p, &n);
      testOomAssertRc(pOom, rc);
      testOomAssert(pOom, rc!=LSM_OK || (n==nVal && memcmp(pVal, p, nVal)==0) );
    }

    lsm_csr_close(pCsr);
    *pRc = rc;
  }
}