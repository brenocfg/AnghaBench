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
 int /*<<< orphan*/  LSM_SEEK_GE ; 
 int /*<<< orphan*/  LSM_SEEK_LE ; 
 int /*<<< orphan*/  lsm_csr_close (int /*<<< orphan*/ *) ; 
 int lsm_csr_key (int /*<<< orphan*/ *,void const**,int*) ; 
 int lsm_csr_next (int /*<<< orphan*/ *) ; 
 int lsm_csr_open (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int lsm_csr_prev (int /*<<< orphan*/ *) ; 
 int lsm_csr_seek (int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lsm_csr_valid (int /*<<< orphan*/ *) ; 
 int lsm_csr_value (int /*<<< orphan*/ *,void const**,int*) ; 
 int /*<<< orphan*/  testOomAssertRc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void testOomScan(
  OomTest *pOom, 
  lsm_db *pDb, 
  int bReverse,
  const void *pKey, int nKey,
  int nScan,
  int *pRc
){
  if( *pRc==0 ){
    int rc;
    int iScan = 0;
    lsm_cursor *pCsr;
    int (*xAdvance)(lsm_cursor *) = 0;
    

    rc = lsm_csr_open(pDb, &pCsr);
    testOomAssertRc(pOom, rc);

    if( rc==LSM_OK ){
      if( bReverse ){
        rc = lsm_csr_seek(pCsr, pKey, nKey, LSM_SEEK_LE);
        xAdvance = lsm_csr_prev;
      }else{
        rc = lsm_csr_seek(pCsr, pKey, nKey, LSM_SEEK_GE);
        xAdvance = lsm_csr_next;
      }
    }
    testOomAssertRc(pOom, rc);

    while( rc==LSM_OK && lsm_csr_valid(pCsr) && iScan<nScan ){
      const void *p; int n;

      rc = lsm_csr_key(pCsr, &p, &n);
      testOomAssertRc(pOom, rc);
      if( rc==LSM_OK ){
        rc = lsm_csr_value(pCsr, &p, &n);
        testOomAssertRc(pOom, rc);
      }
      if( rc==LSM_OK ){
        rc = xAdvance(pCsr);
        testOomAssertRc(pOom, rc);
      }
      iScan++;
    }

    lsm_csr_close(pCsr);
    *pRc = rc;
  }
}