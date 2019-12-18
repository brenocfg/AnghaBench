#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_25__ {scalar_t__ iId; } ;
struct TYPE_27__ {int nMaxFreelist; TYPE_3__ compress; int /*<<< orphan*/  pEnv; TYPE_6__* pWorker; int /*<<< orphan*/ * pFS; } ;
typedef  TYPE_5__ lsm_db ;
typedef  int i64 ;
struct TYPE_31__ {scalar_t__ aCkpt; int /*<<< orphan*/  pEnv; } ;
struct TYPE_30__ {int iBlk; int iId; } ;
struct TYPE_29__ {struct TYPE_29__* pNext; } ;
struct TYPE_26__ {int nEntry; TYPE_8__* aEntry; } ;
struct TYPE_24__ {int n; TYPE_1__* a; } ;
struct TYPE_28__ {scalar_t__ iCmpId; int nBlock; int nWrite; TYPE_4__ freelist; TYPE_2__ redirect; } ;
struct TYPE_23__ {int iFrom; int iTo; } ;
typedef  TYPE_6__ Snapshot ;
typedef  TYPE_7__ Level ;
typedef  TYPE_8__ FreelistEntry ;
typedef  int /*<<< orphan*/  FileSystem ;
typedef  TYPE_9__ CkptBuffer ;

/* Variables and functions */
 int CKPT_HDR_BLKSZ ; 
 int CKPT_HDR_CMPID ; 
 int CKPT_HDR_ID_LSW ; 
 int CKPT_HDR_ID_MSW ; 
 int CKPT_HDR_NBLOCK ; 
 int CKPT_HDR_NCKPT ; 
 int CKPT_HDR_NLEVEL ; 
 int CKPT_HDR_NWRITE ; 
 int CKPT_HDR_PGSZ ; 
 int CKPT_HDR_SIZE ; 
 scalar_t__ LSM_COMPRESSION_EMPTY ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ckptAddChecksum (TYPE_9__*,int,int*) ; 
 int /*<<< orphan*/  ckptExportAppendlist (TYPE_5__*,TYPE_9__*,int*,int*) ; 
 int /*<<< orphan*/  ckptExportLevel (TYPE_7__*,TYPE_9__*,int*,int*) ; 
 int /*<<< orphan*/  ckptExportLog (TYPE_5__*,int,TYPE_9__*,int*,int*) ; 
 int /*<<< orphan*/  ckptSetValue (TYPE_9__*,int,int,int*) ; 
 TYPE_7__* lsmDbSnapshotLevel (TYPE_6__*) ; 
 int lsmFsBlockSize (int /*<<< orphan*/ *) ; 
 int lsmFsPageSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmLogMessage (TYPE_5__*,int,char*,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ckptExportSnapshot( 
  lsm_db *pDb,                    /* Connection handle */
  int bLog,                       /* True to update log-offset fields */
  i64 iId,                        /* Checkpoint id */
  int bCksum,                     /* If true, include checksums */
  void **ppCkpt,                  /* OUT: Buffer containing checkpoint */
  int *pnCkpt                     /* OUT: Size of checkpoint in bytes */
){
  int rc = LSM_OK;                /* Return Code */
  FileSystem *pFS = pDb->pFS;     /* File system object */
  Snapshot *pSnap = pDb->pWorker; /* Worker snapshot */
  int nLevel = 0;                 /* Number of levels in checkpoint */
  int iLevel;                     /* Used to count out nLevel levels */
  int iOut = 0;                   /* Current offset in aCkpt[] */
  Level *pLevel;                  /* Level iterator */
  int i;                          /* Iterator used while serializing freelist */
  CkptBuffer ckpt;

  /* Initialize the output buffer */
  memset(&ckpt, 0, sizeof(CkptBuffer));
  ckpt.pEnv = pDb->pEnv;
  iOut = CKPT_HDR_SIZE;

  /* Write the log offset into the checkpoint. */
  ckptExportLog(pDb, bLog, &ckpt, &iOut, &rc);

  /* Write the append-point list */
  ckptExportAppendlist(pDb, &ckpt, &iOut, &rc);

  /* Figure out how many levels will be written to the checkpoint. */
  for(pLevel=lsmDbSnapshotLevel(pSnap); pLevel; pLevel=pLevel->pNext) nLevel++;

  /* Serialize nLevel levels. */
  iLevel = 0;
  for(pLevel=lsmDbSnapshotLevel(pSnap); iLevel<nLevel; pLevel=pLevel->pNext){
    ckptExportLevel(pLevel, &ckpt, &iOut, &rc);
    iLevel++;
  }

  /* Write the block-redirect list */
  ckptSetValue(&ckpt, iOut++, pSnap->redirect.n, &rc);
  for(i=0; i<pSnap->redirect.n; i++){
    ckptSetValue(&ckpt, iOut++, pSnap->redirect.a[i].iFrom, &rc);
    ckptSetValue(&ckpt, iOut++, pSnap->redirect.a[i].iTo, &rc);
  }

  /* Write the freelist */
  assert( pSnap->freelist.nEntry<=pDb->nMaxFreelist );
  if( rc==LSM_OK ){
    int nFree = pSnap->freelist.nEntry;
    ckptSetValue(&ckpt, iOut++, nFree, &rc);
    for(i=0; i<nFree; i++){
      FreelistEntry *p = &pSnap->freelist.aEntry[i];
      ckptSetValue(&ckpt, iOut++, p->iBlk, &rc);
      ckptSetValue(&ckpt, iOut++, (p->iId >> 32) & 0xFFFFFFFF, &rc);
      ckptSetValue(&ckpt, iOut++, p->iId & 0xFFFFFFFF, &rc);
    }
  }

  /* Write the checkpoint header */
  assert( iId>=0 );
  assert( pSnap->iCmpId==pDb->compress.iId
       || pSnap->iCmpId==LSM_COMPRESSION_EMPTY 
  );
  ckptSetValue(&ckpt, CKPT_HDR_ID_MSW, (u32)(iId>>32), &rc);
  ckptSetValue(&ckpt, CKPT_HDR_ID_LSW, (u32)(iId&0xFFFFFFFF), &rc);
  ckptSetValue(&ckpt, CKPT_HDR_NCKPT, iOut+2, &rc);
  ckptSetValue(&ckpt, CKPT_HDR_CMPID, pDb->compress.iId, &rc);
  ckptSetValue(&ckpt, CKPT_HDR_NBLOCK, pSnap->nBlock, &rc);
  ckptSetValue(&ckpt, CKPT_HDR_BLKSZ, lsmFsBlockSize(pFS), &rc);
  ckptSetValue(&ckpt, CKPT_HDR_NLEVEL, nLevel, &rc);
  ckptSetValue(&ckpt, CKPT_HDR_PGSZ, lsmFsPageSize(pFS), &rc);
  ckptSetValue(&ckpt, CKPT_HDR_NWRITE, pSnap->nWrite, &rc);

  if( bCksum ){
    ckptAddChecksum(&ckpt, iOut, &rc);
  }else{
    ckptSetValue(&ckpt, iOut, 0, &rc);
    ckptSetValue(&ckpt, iOut+1, 0, &rc);
  }
  iOut += 2;
  assert( iOut<=1024 );

#ifdef LSM_LOG_FREELIST
  lsmLogMessage(pDb, rc, 
      "ckptExportSnapshot(): id=%lld freelist: %d", iId, pSnap->freelist.nEntry
  );
  for(i=0; i<pSnap->freelist.nEntry; i++){
  lsmLogMessage(pDb, rc, 
      "ckptExportSnapshot(): iBlk=%d id=%lld", 
      pSnap->freelist.aEntry[i].iBlk,
      pSnap->freelist.aEntry[i].iId
  );
  }
#endif

  *ppCkpt = (void *)ckpt.aCkpt;
  if( pnCkpt ) *pnCkpt = sizeof(u32)*iOut;
  return rc;
}