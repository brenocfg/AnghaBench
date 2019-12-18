#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {TYPE_3__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
typedef  scalar_t__ i64 ;
struct TYPE_8__ {TYPE_2__* aReader; } ;
struct TYPE_7__ {scalar_t__ iLsmId; scalar_t__ iTreeId; } ;
typedef  TYPE_2__ ShmReader ;
typedef  TYPE_3__ ShmHeader ;

/* Variables and functions */
 int LSM_BUSY ; 
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int LSM_LOCK_NREADER ; 
 int /*<<< orphan*/  LSM_LOCK_READER (int) ; 
 int /*<<< orphan*/  LSM_LOCK_UNLOCK ; 
 int LSM_OK ; 
 int lsmShmLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbSetReadLock(lsm_db *db, i64 iLsm, u32 iShm){
  int rc = LSM_OK;
  ShmHeader *pShm = db->pShmhdr;
  int i;

  /* Check if there is already a slot containing the required values. */
  for(i=0; i<LSM_LOCK_NREADER; i++){
    ShmReader *p = &pShm->aReader[i];
    if( p->iLsmId==iLsm && p->iTreeId==iShm ) return LSM_OK;
  }

  /* Iterate through all read-lock slots, attempting to take a write-lock
  ** on each of them. If a write-lock succeeds, populate the locked slot
  ** with the required values and break out of the loop.  */
  for(i=0; rc==LSM_OK && i<LSM_LOCK_NREADER; i++){
    rc = lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_EXCL, 0);
    if( rc==LSM_BUSY ){
      rc = LSM_OK;
    }else{
      ShmReader *p = &pShm->aReader[i];
      p->iLsmId = iLsm;
      p->iTreeId = iShm;
      lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_UNLOCK, 0);
      break;
    }
  }

  return rc;
}