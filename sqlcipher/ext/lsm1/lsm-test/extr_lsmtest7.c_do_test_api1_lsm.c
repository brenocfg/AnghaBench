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

/* Variables and functions */
 int LSM_MISUSE ; 
 int LSM_OK ; 
 int /*<<< orphan*/  LSM_SEEK_EQ ; 
 int /*<<< orphan*/  LSM_SEEK_GE ; 
 int /*<<< orphan*/  LSM_SEEK_LE ; 
 int /*<<< orphan*/  LSM_SEEK_LEFAST ; 
 int /*<<< orphan*/  lsm_csr_close (int /*<<< orphan*/ *) ; 
 int lsm_csr_first (int /*<<< orphan*/ *) ; 
 int lsm_csr_key (int /*<<< orphan*/ *,void const**,int*) ; 
 int lsm_csr_last (int /*<<< orphan*/ *) ; 
 int lsm_csr_next (int /*<<< orphan*/ *) ; 
 int lsm_csr_open (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int lsm_csr_prev (int /*<<< orphan*/ *) ; 
 int lsm_csr_seek (int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ) ; 
 int lsm_csr_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testCompareInt (int,int,int*) ; 

__attribute__((used)) static void do_test_api1_lsm(lsm_db *pDb, int *pRc){
  int ret;
  lsm_cursor *pCsr;
  lsm_cursor *pCsr2;
  int nKey;
  const void *pKey;

  ret = lsm_csr_open(pDb, &pCsr);
  testCompareInt(LSM_OK, ret, pRc);

  ret = lsm_csr_next(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);
  ret = lsm_csr_prev(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);

  ret = lsm_csr_seek(pCsr, "jjj", 3, LSM_SEEK_GE);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_next(pCsr);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_prev(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);

  ret = lsm_csr_seek(pCsr, "jjj", 3, LSM_SEEK_LE);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_next(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);
  ret = lsm_csr_prev(pCsr);
  testCompareInt(LSM_OK, ret, pRc);

  ret = lsm_csr_seek(pCsr, "jjj", 3, LSM_SEEK_LEFAST);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_next(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);
  ret = lsm_csr_prev(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);

  ret = lsm_csr_key(pCsr, &pKey, &nKey);
  testCompareInt(LSM_OK, ret, pRc);

  ret = lsm_csr_open(pDb, &pCsr2);
  testCompareInt(LSM_OK, ret, pRc);

  ret = lsm_csr_seek(pCsr2, pKey, nKey, LSM_SEEK_EQ);
  testCompareInt(LSM_OK, ret, pRc);
  testCompareInt(1, lsm_csr_valid(pCsr2), pRc);
  ret = lsm_csr_next(pCsr2);
  testCompareInt(LSM_MISUSE, ret, pRc);
  ret = lsm_csr_prev(pCsr2);
  testCompareInt(LSM_MISUSE, ret, pRc);

  lsm_csr_close(pCsr2);

  ret = lsm_csr_first(pCsr);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_next(pCsr);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_prev(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);

  ret = lsm_csr_last(pCsr);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_prev(pCsr);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_next(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);

  ret = lsm_csr_first(pCsr);
  while( lsm_csr_valid(pCsr) ){
    ret = lsm_csr_next(pCsr);
    testCompareInt(LSM_OK, ret, pRc);
  }
  ret = lsm_csr_next(pCsr);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_prev(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);

  ret = lsm_csr_last(pCsr);
  while( lsm_csr_valid(pCsr) ){
    ret = lsm_csr_prev(pCsr);
    testCompareInt(LSM_OK, ret, pRc);
  }
  ret = lsm_csr_prev(pCsr);
  testCompareInt(LSM_OK, ret, pRc);
  ret = lsm_csr_next(pCsr);
  testCompareInt(LSM_MISUSE, ret, pRc);

  lsm_csr_close(pCsr);
}