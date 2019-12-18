#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nTransOpen; TYPE_2__* aTrans; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_10__ {int /*<<< orphan*/  log; int /*<<< orphan*/  tree; } ;
typedef  TYPE_2__ TransMark ;

/* Variables and functions */
 int LSM_MAX (int /*<<< orphan*/ ,int) ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert_db_state (TYPE_1__*) ; 
 int /*<<< orphan*/  dbReleaseClientSnapshot (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmFinishWriteTrans (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmLogSeek (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmTreeRollback (TYPE_1__*,int /*<<< orphan*/ *) ; 

int lsm_rollback(lsm_db *pDb, int iLevel){
  int rc = LSM_OK;
  assert_db_state( pDb );

  if( pDb->nTransOpen ){
    /* A value less than zero means close the innermost nested transaction. */
    if( iLevel<0 ) iLevel = LSM_MAX(0, pDb->nTransOpen - 1);

    if( iLevel<=pDb->nTransOpen ){
      TransMark *pMark = &pDb->aTrans[(iLevel==0 ? 0 : iLevel-1)];
      lsmTreeRollback(pDb, &pMark->tree);
      if( iLevel ) lsmLogSeek(pDb, &pMark->log);
      pDb->nTransOpen = iLevel;
    }

    if( pDb->nTransOpen==0 ){
      lsmFinishWriteTrans(pDb, 0);
    }
    dbReleaseClientSnapshot(pDb);
  }

  return rc;
}