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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {TYPE_3__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
typedef  scalar_t__ i64 ;
struct TYPE_8__ {TYPE_2__* aReader; } ;
struct TYPE_7__ {scalar_t__ iLsmId; int /*<<< orphan*/  iTreeId; } ;
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
 scalar_t__ shm_sequence_ge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isInUse(lsm_db *db, i64 iLsmId, u32 iShmid, int *pbInUse){
  ShmHeader *pShm = db->pShmhdr;
  int i;
  int rc = LSM_OK;

  for(i=0; rc==LSM_OK && i<LSM_LOCK_NREADER; i++){
    ShmReader *p = &pShm->aReader[i];
    if( p->iLsmId ){
      if( (iLsmId!=0 && p->iLsmId!=0 && iLsmId>=p->iLsmId) 
       || (iLsmId==0 && shm_sequence_ge(p->iTreeId, iShmid))
      ){
        rc = lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_EXCL, 0);
        if( rc==LSM_OK ){
          p->iLsmId = 0;
          lsmShmLock(db, LSM_LOCK_READER(i), LSM_LOCK_UNLOCK, 0);
        }
      }
    }
  }

  if( rc==LSM_BUSY ){
    *pbInUse = 1;
    return LSM_OK;
  }
  *pbInUse = 0;
  return rc;
}