#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  iUsedShmid; } ;
struct TYPE_10__ {scalar_t__ iReader; TYPE_6__* pWorker; int /*<<< orphan*/  pEnv; TYPE_1__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_11__ {int /*<<< orphan*/  iId; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_LOCK_UNLOCK ; 
 int /*<<< orphan*/  LSM_LOCK_WORKER ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int dbSetReadLock (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmFreeSnapshot (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int lsmSaveWorker (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lsmShmLock (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lsmTreeLoadHeader (TYPE_2__*,int /*<<< orphan*/ ) ; 

void lsmFinishWork(lsm_db *pDb, int bFlush, int *pRc){
  int rc = *pRc;
  assert( rc!=0 || pDb->pWorker );
  if( pDb->pWorker ){
    /* If no error has occurred, serialize the worker snapshot and write
    ** it to shared memory.  */
    if( rc==LSM_OK ){
      rc = lsmSaveWorker(pDb, bFlush);
    }

    /* Assuming no error has occurred, update a read lock slot with the
    ** new snapshot id (see comments above function dbSetReadLock()).  */
    if( rc==LSM_OK ){
      if( pDb->iReader<0 ){
        rc = lsmTreeLoadHeader(pDb, 0);
      }
      if( rc==LSM_OK ){
        rc = dbSetReadLock(pDb, pDb->pWorker->iId, pDb->treehdr.iUsedShmid);
      }
    }

    /* Free the snapshot object. */
    lsmFreeSnapshot(pDb->pEnv, pDb->pWorker);
    pDb->pWorker = 0;
  }

  lsmShmLock(pDb, LSM_LOCK_WORKER, LSM_LOCK_UNLOCK, 0);
  *pRc = rc;
}