#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_7__ {int iReader; scalar_t__ bRoTrans; TYPE_3__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
typedef  scalar_t__ i64 ;
struct TYPE_9__ {TYPE_2__* aReader; } ;
struct TYPE_8__ {scalar_t__ iLsmId; scalar_t__ iTreeId; } ;
typedef  TYPE_2__ ShmReader ;
typedef  TYPE_3__ ShmHeader ;

/* Variables and functions */
 int LSM_BUSY ; 
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int LSM_LOCK_NREADER ; 
 int /*<<< orphan*/  LSM_LOCK_READER (int) ; 
 int /*<<< orphan*/  LSM_LOCK_SHARED ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmShmLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int shm_sequence_ge (scalar_t__,scalar_t__) ; 
 scalar_t__ slotIsUsable (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 

int lsmReadlock(lsm_db *db, i64 iLsm, u32 iShmMin, u32 iShmMax){
  int rc = LSM_OK;
  ShmHeader *pShm = db->pShmhdr;
  int i;

  assert( db->iReader<0 );
  assert( shm_sequence_ge(iShmMax, iShmMin) );

  /* This is a no-op if the read-only transaction flag is set. */
  if( db->bRoTrans ){
    db->iReader = 0;
    return LSM_OK;
  }

  /* Search for an exact match. */
  for(i=0; db->iReader<0 && rc==LSM_OK && i<LSM_LOCK_NREADER; i++){
    ShmReader *p = &pShm->aReader[i];
    if( p->iLsmId==iLsm && p->iTreeId==iShmMax ){
      rc = lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_SHARED, 0);
      if( rc==LSM_OK && p->iLsmId==iLsm && p->iTreeId==iShmMax ){
        db->iReader = i;
      }else if( rc==LSM_BUSY ){
        rc = LSM_OK;
      }
    }
  }

  /* Try to obtain a write-lock on each slot, in order. If successful, set
  ** the slot values to iLsm/iTree.  */
  for(i=0; db->iReader<0 && rc==LSM_OK && i<LSM_LOCK_NREADER; i++){
    rc = lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_EXCL, 0);
    if( rc==LSM_BUSY ){
      rc = LSM_OK;
    }else{
      ShmReader *p = &pShm->aReader[i];
      p->iLsmId = iLsm;
      p->iTreeId = iShmMax;
      rc = lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_SHARED, 0);
      assert( rc!=LSM_BUSY );
      if( rc==LSM_OK ) db->iReader = i;
    }
  }

  /* Search for any usable slot */
  for(i=0; db->iReader<0 && rc==LSM_OK && i<LSM_LOCK_NREADER; i++){
    ShmReader *p = &pShm->aReader[i];
    if( slotIsUsable(p, iLsm, iShmMin, iShmMax) ){
      rc = lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_SHARED, 0);
      if( rc==LSM_OK && slotIsUsable(p, iLsm, iShmMin, iShmMax) ){
        db->iReader = i;
      }else if( rc==LSM_BUSY ){
        rc = LSM_OK;
      }
    }
  }

  if( rc==LSM_OK && db->iReader<0 ){
    rc = LSM_BUSY;
  }
  return rc;
}