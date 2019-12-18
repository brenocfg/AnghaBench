#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nTransOpen; scalar_t__ eSafety; int /*<<< orphan*/  pFS; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int LSM_MAX (int /*<<< orphan*/ ,int) ; 
 int LSM_OK ; 
 scalar_t__ LSM_SAFETY_FULL ; 
 int /*<<< orphan*/  assert_db_state (TYPE_1__*) ; 
 int /*<<< orphan*/  dbReleaseClientSnapshot (TYPE_1__*) ; 
 int lsmFinishWriteTrans (TYPE_1__*,int) ; 
 int lsmFsSyncLog (int /*<<< orphan*/ ) ; 
 int lsmLogCommit (TYPE_1__*) ; 

int lsm_commit(lsm_db *pDb, int iLevel){
  int rc = LSM_OK;

  assert_db_state( pDb );

  /* A value less than zero means close the innermost nested transaction. */
  if( iLevel<0 ) iLevel = LSM_MAX(0, pDb->nTransOpen - 1);

  if( iLevel<pDb->nTransOpen ){
    if( iLevel==0 ){
      int rc2;
      /* Commit the transaction to disk. */
      if( rc==LSM_OK ) rc = lsmLogCommit(pDb);
      if( rc==LSM_OK && pDb->eSafety==LSM_SAFETY_FULL ){
        rc = lsmFsSyncLog(pDb->pFS);
      }
      rc2 = lsmFinishWriteTrans(pDb, (rc==LSM_OK));
      if( rc==LSM_OK ) rc = rc2;
    }
    pDb->nTransOpen = iLevel;
  }
  dbReleaseClientSnapshot(pDb);
  return rc;
}