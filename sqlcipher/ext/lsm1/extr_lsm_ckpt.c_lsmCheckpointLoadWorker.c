#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {TYPE_7__* pWorker; int /*<<< orphan*/  pDatabase; TYPE_2__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_11__ {int /*<<< orphan*/  iCmpId; int /*<<< orphan*/  pDatabase; } ;
struct TYPE_10__ {int* aSnap1; int* aSnap2; } ;
typedef  TYPE_2__ ShmHeader ;

/* Variables and functions */
 size_t CKPT_HDR_NCKPT ; 
 int /*<<< orphan*/  LSM_LOCK_DMS1 ; 
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int /*<<< orphan*/  LSM_LOCK_WORKER ; 
 int LSM_OK ; 
 int LSM_PROTOCOL_BKPT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ckptChecksumOk (int*) ; 
 int lsmCheckCompressionId (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lsmCheckpointDeserialize (TYPE_1__*,int,int*,TYPE_7__**) ; 
 scalar_t__ lsmFsIntegrityCheck (TYPE_1__*) ; 
 scalar_t__ lsmShmAssertLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int lsmCheckpointLoadWorker(lsm_db *pDb){
  int rc;
  ShmHeader *pShm = pDb->pShmhdr;
  int nInt1;
  int nInt2;

  /* Must be holding the WORKER lock to do this. Or DMS2. */
  assert( 
      lsmShmAssertLock(pDb, LSM_LOCK_WORKER, LSM_LOCK_EXCL) 
   || lsmShmAssertLock(pDb, LSM_LOCK_DMS1, LSM_LOCK_EXCL) 
  );

  /* Check that the two snapshots match. If not, repair them. */
  nInt1 = pShm->aSnap1[CKPT_HDR_NCKPT];
  nInt2 = pShm->aSnap2[CKPT_HDR_NCKPT];
  if( nInt1!=nInt2 || memcmp(pShm->aSnap1, pShm->aSnap2, nInt2*sizeof(u32)) ){
    if( ckptChecksumOk(pShm->aSnap1) ){
      memcpy(pShm->aSnap2, pShm->aSnap1, sizeof(u32)*nInt1);
    }else if( ckptChecksumOk(pShm->aSnap2) ){
      memcpy(pShm->aSnap1, pShm->aSnap2, sizeof(u32)*nInt2);
    }else{
      return LSM_PROTOCOL_BKPT;
    }
  }

  rc = lsmCheckpointDeserialize(pDb, 1, pShm->aSnap1, &pDb->pWorker);
  if( pDb->pWorker ) pDb->pWorker->pDatabase = pDb->pDatabase;

  if( rc==LSM_OK ){
    rc = lsmCheckCompressionId(pDb, pDb->pWorker->iCmpId);
  }

#if 0
  assert( rc!=LSM_OK || lsmFsIntegrityCheck(pDb) );
#endif
  return rc;
}