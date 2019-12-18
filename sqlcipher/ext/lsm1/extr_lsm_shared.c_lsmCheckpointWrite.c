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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_9__ {scalar_t__ pWorker; scalar_t__ pClient; scalar_t__ eSafety; scalar_t__* aSnapshot; int /*<<< orphan*/  pFS; TYPE_2__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
typedef  scalar_t__ i64 ;
struct TYPE_10__ {int iMetaPage; } ;
typedef  TYPE_2__ ShmHeader ;
typedef  int /*<<< orphan*/  MetaPage ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_LOCK_CHECKPOINTER ; 
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int /*<<< orphan*/  LSM_LOCK_UNLOCK ; 
 int /*<<< orphan*/  LSM_LOCK_WORKER ; 
 int LSM_OK ; 
 scalar_t__ LSM_SAFETY_OFF ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ lsmCheckpointId (scalar_t__*,int) ; 
 int lsmCheckpointLoad (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lsmCheckpointNBlock (scalar_t__*) ; 
 scalar_t__ lsmCheckpointNWrite (scalar_t__*,int) ; 
 int lsmCheckpointStore (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * lsmFsMetaPageData (int /*<<< orphan*/ *,int*) ; 
 int lsmFsMetaPageGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsMetaPageRelease (int /*<<< orphan*/ *) ; 
 int lsmFsSyncDb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lsmLogMessage (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int lsmShmAssertLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lsmShmLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lsmCheckpointWrite(lsm_db *pDb, u32 *pnWrite){
  int rc;                         /* Return Code */
  u32 nWrite = 0;

  assert( pDb->pWorker==0 );
  assert( 1 || pDb->pClient==0 );
  assert( lsmShmAssertLock(pDb, LSM_LOCK_WORKER, LSM_LOCK_UNLOCK) );

  rc = lsmShmLock(pDb, LSM_LOCK_CHECKPOINTER, LSM_LOCK_EXCL, 0);
  if( rc!=LSM_OK ) return rc;

  rc = lsmCheckpointLoad(pDb, 0);
  if( rc==LSM_OK ){
    int nBlock = lsmCheckpointNBlock(pDb->aSnapshot);
    ShmHeader *pShm = pDb->pShmhdr;
    int bDone = 0;                /* True if checkpoint is already stored */

    /* Check if this checkpoint has already been written to the database
    ** file. If so, set variable bDone to true.  */
    if( pShm->iMetaPage ){
      MetaPage *pPg;              /* Meta page */
      u8 *aData;                  /* Meta-page data buffer */
      int nData;                  /* Size of aData[] in bytes */
      i64 iCkpt;                  /* Id of checkpoint just loaded */
      i64 iDisk = 0;              /* Id of checkpoint already stored in db */
      iCkpt = lsmCheckpointId(pDb->aSnapshot, 0);
      rc = lsmFsMetaPageGet(pDb->pFS, 0, pShm->iMetaPage, &pPg);
      if( rc==LSM_OK ){
        aData = lsmFsMetaPageData(pPg, &nData);
        iDisk = lsmCheckpointId((u32 *)aData, 1);
        nWrite = lsmCheckpointNWrite((u32 *)aData, 1);
        lsmFsMetaPageRelease(pPg);
      }
      bDone = (iDisk>=iCkpt);
    }

    if( rc==LSM_OK && bDone==0 ){
      int iMeta = (pShm->iMetaPage % 2) + 1;
      if( pDb->eSafety!=LSM_SAFETY_OFF ){
        rc = lsmFsSyncDb(pDb->pFS, nBlock);
      }
      if( rc==LSM_OK ) rc = lsmCheckpointStore(pDb, iMeta);
      if( rc==LSM_OK && pDb->eSafety!=LSM_SAFETY_OFF){
        rc = lsmFsSyncDb(pDb->pFS, 0);
      }
      if( rc==LSM_OK ){
        pShm->iMetaPage = iMeta;
        nWrite = lsmCheckpointNWrite(pDb->aSnapshot, 0) - nWrite;
      }
#ifdef LSM_LOG_WORK
      lsmLogMessage(pDb, 0, "finish checkpoint %d", 
          (int)lsmCheckpointId(pDb->aSnapshot, 0)
      );
#endif
    }
  }

  lsmShmLock(pDb, LSM_LOCK_CHECKPOINTER, LSM_LOCK_UNLOCK, 0);
  if( pnWrite && rc==LSM_OK ) *pnWrite = nWrite;
  return rc;
}