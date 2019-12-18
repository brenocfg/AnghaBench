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
typedef  int /*<<< orphan*/  lsm_cursor ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {int nBuf; int /*<<< orphan*/ * pCsr; void* pBuf; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ LsmDb ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  LSM_SEEK_EQ ; 
 int /*<<< orphan*/  lsm_csr_close (int /*<<< orphan*/ *) ; 
 int lsm_csr_open (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int lsm_csr_seek (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lsm_csr_valid (int /*<<< orphan*/ *) ; 
 int lsm_csr_value (int /*<<< orphan*/ *,void const**,int*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int /*<<< orphan*/  testFree (void*) ; 
 void* testMalloc (int) ; 

__attribute__((used)) static int test_lsm_fetch(
  TestDb *pTestDb, 
  void *pKey, 
  int nKey, 
  void **ppVal, 
  int *pnVal
){
  int rc;
  LsmDb *pDb = (LsmDb *)pTestDb;
  lsm_cursor *csr;

  if( pKey==0 ) return LSM_OK;

  if( pDb->pCsr==0 ){
    rc = lsm_csr_open(pDb->db, &csr);
    if( rc!=LSM_OK ) return rc;
  }else{
    csr = pDb->pCsr;
  }

  rc = lsm_csr_seek(csr, pKey, nKey, LSM_SEEK_EQ);
  if( rc==LSM_OK ){
    if( lsm_csr_valid(csr) ){
      const void *pVal; int nVal;
      rc = lsm_csr_value(csr, &pVal, &nVal);
      if( nVal>pDb->nBuf ){
        testFree(pDb->pBuf);
        pDb->pBuf = testMalloc(nVal*2);
        pDb->nBuf = nVal*2;
      }
      memcpy(pDb->pBuf, pVal, nVal);
      *ppVal = pDb->pBuf;
      *pnVal = nVal;
    }else{
      *ppVal = 0;
      *pnVal = -1;
    }
  }
  if( pDb->pCsr==0 ){
    lsm_csr_close(csr);
  }
  return rc;
}