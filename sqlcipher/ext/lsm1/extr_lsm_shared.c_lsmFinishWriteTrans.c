#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  iUsedShmid; } ;
struct TYPE_15__ {scalar_t__ nTreeLimit; scalar_t__ bAutowork; int /*<<< orphan*/  pWorkCtx; int /*<<< orphan*/  (* xWork ) (TYPE_3__*,int /*<<< orphan*/ ) ;scalar_t__ bDiscardOld; TYPE_2__ treehdr; TYPE_1__* pClient; } ;
typedef  TYPE_3__ lsm_db ;
struct TYPE_13__ {int /*<<< orphan*/  iId; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_LOCK_UNLOCK ; 
 int /*<<< orphan*/  LSM_LOCK_WRITER ; 
 int LSM_OK ; 
 int dbSetReadLock (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmLogEnd (TYPE_3__*,int) ; 
 int /*<<< orphan*/  lsmShmLock (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lsmSortedAutoWork (TYPE_3__*,int) ; 
 int /*<<< orphan*/  lsmTreeEndTransaction (TYPE_3__*,int) ; 
 int /*<<< orphan*/  lsmTreeMakeOld (TYPE_3__*) ; 
 scalar_t__ lsmTreeSize (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

int lsmFinishWriteTrans(lsm_db *pDb, int bCommit){
  int rc = LSM_OK;
  int bFlush = 0;

  lsmLogEnd(pDb, bCommit);
  if( rc==LSM_OK && bCommit && lsmTreeSize(pDb)>pDb->nTreeLimit ){
    bFlush = 1;
    lsmTreeMakeOld(pDb);
  }
  lsmTreeEndTransaction(pDb, bCommit);

  if( rc==LSM_OK ){
    if( bFlush && pDb->bAutowork ){
      rc = lsmSortedAutoWork(pDb, 1);
    }else if( bCommit && pDb->bDiscardOld ){
      rc = dbSetReadLock(pDb, pDb->pClient->iId, pDb->treehdr.iUsedShmid);
    }
  }
  pDb->bDiscardOld = 0;
  lsmShmLock(pDb, LSM_LOCK_WRITER, LSM_LOCK_UNLOCK, 0);

  if( bFlush && pDb->bAutowork==0 && pDb->xWork ){
    pDb->xWork(pDb, pDb->pWorkCtx);
  }
  return rc;
}