#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ iReader; int bRoTrans; scalar_t__* apShm; int /*<<< orphan*/ * pShmhdr; scalar_t__ bReadonly; } ;
typedef  TYPE_1__ lsm_db ;
typedef  int /*<<< orphan*/  ShmHeader ;

/* Variables and functions */
 int LSM_BUSY ; 
 int /*<<< orphan*/  LSM_LOCK_DMS1 ; 
 int /*<<< orphan*/  LSM_LOCK_DMS3 ; 
 int /*<<< orphan*/  LSM_LOCK_NREADER ; 
 int /*<<< orphan*/  LSM_LOCK_ROTRANS ; 
 int /*<<< orphan*/  LSM_LOCK_RWCLIENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSM_LOCK_SHARED ; 
 int /*<<< orphan*/  LSM_LOCK_UNLOCK ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmBeginReadTrans (TYPE_1__*) ; 
 int lsmCheckpointRecover (TYPE_1__*) ; 
 int lsmLogRecover (TYPE_1__*) ; 
 int lsmShmCacheChunks (TYPE_1__*,int) ; 
 int lsmShmLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lsmShmTestLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int lsmBeginRoTrans(lsm_db *db){
  int rc = LSM_OK;

  assert( db->bReadonly && db->pShmhdr==0 );
  assert( db->iReader<0 );

  if( db->bRoTrans==0 ){

    /* Attempt a shared-lock on DMS1. */
    rc = lsmShmLock(db, LSM_LOCK_DMS1, LSM_LOCK_SHARED, 0);
    if( rc!=LSM_OK ) return rc;

    rc = lsmShmTestLock(
        db, LSM_LOCK_RWCLIENT(0), LSM_LOCK_NREADER, LSM_LOCK_SHARED
    );
    if( rc==LSM_OK ){
      /* System is not live. Take a SHARED lock on the ROTRANS byte and
      ** release DMS1. Locking ROTRANS tells all read-write clients that they
      ** may not recycle any disk space from within the database or log files,
      ** as a read-only client may be using it.  */
      rc = lsmShmLock(db, LSM_LOCK_ROTRANS, LSM_LOCK_SHARED, 0);
      lsmShmLock(db, LSM_LOCK_DMS1, LSM_LOCK_UNLOCK, 0);

      if( rc==LSM_OK ){
        db->bRoTrans = 1;
        rc = lsmShmCacheChunks(db, 1);
        if( rc==LSM_OK ){
          db->pShmhdr = (ShmHeader *)db->apShm[0];
          memset(db->pShmhdr, 0, sizeof(ShmHeader));
          rc = lsmCheckpointRecover(db);
          if( rc==LSM_OK ){
            rc = lsmLogRecover(db);
          }
        }
      }
    }else if( rc==LSM_BUSY ){
      /* System is live! */
      rc = lsmShmLock(db, LSM_LOCK_DMS3, LSM_LOCK_SHARED, 0);
      lsmShmLock(db, LSM_LOCK_DMS1, LSM_LOCK_UNLOCK, 0);
      if( rc==LSM_OK ){
        rc = lsmShmCacheChunks(db, 1);
        if( rc==LSM_OK ){
          db->pShmhdr = (ShmHeader *)db->apShm[0];
        }
      }
    }

    if( rc==LSM_OK ){
      rc = lsmBeginReadTrans(db);
    }
  }

  return rc;
}