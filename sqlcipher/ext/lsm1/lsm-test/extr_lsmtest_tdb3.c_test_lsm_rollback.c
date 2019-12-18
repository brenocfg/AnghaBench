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
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {int /*<<< orphan*/  db; scalar_t__ pCsr; } ;
typedef  TYPE_1__ LsmDb ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lsm_csr_close (scalar_t__) ; 
 int lsm_rollback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_lsm_rollback(TestDb *pTestDb, int iLevel){
  LsmDb *pDb = (LsmDb *)pTestDb;

  /* If iLevel==0, close any open read transaction */
  if( iLevel==0 && pDb->pCsr ){
    lsm_csr_close(pDb->pCsr);
    pDb->pCsr = 0;
  }

  return lsm_rollback(pDb->db, MAX(0, iLevel-1));
}