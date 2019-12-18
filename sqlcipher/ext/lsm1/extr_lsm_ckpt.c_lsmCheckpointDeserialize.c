#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct RedirectEntry {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_5__ lsm_db ;
typedef  int i64 ;
struct TYPE_23__ {void* iTo; void* iFrom; } ;
struct TYPE_22__ {void* iId; void* iBlk; } ;
struct TYPE_16__ {TYPE_3__* pRedirect; } ;
struct TYPE_21__ {int nRight; TYPE_2__ lhs; TYPE_1__* aRhs; struct TYPE_21__* pNext; } ;
struct TYPE_18__ {int nEntry; int nAlloc; TYPE_8__* aEntry; } ;
struct TYPE_17__ {int n; TYPE_9__* a; } ;
struct TYPE_20__ {TYPE_4__ freelist; TYPE_3__ redirect; TYPE_7__* pLevel; int /*<<< orphan*/ * aiAppend; void* iCmpId; int /*<<< orphan*/  iLogOff; void* nWrite; void* nBlock; int /*<<< orphan*/  iId; } ;
struct TYPE_15__ {TYPE_3__* pRedirect; } ;
typedef  TYPE_6__ Snapshot ;
typedef  TYPE_7__ Level ;
typedef  TYPE_8__ FreelistEntry ;

/* Variables and functions */
 int CKPT_APPENDLIST_SIZE ; 
 size_t CKPT_HDR_CMPID ; 
 size_t CKPT_HDR_NBLOCK ; 
 size_t CKPT_HDR_NLEVEL ; 
 size_t CKPT_HDR_NWRITE ; 
 int CKPT_HDR_SIZE ; 
 int CKPT_LOGPTR_SIZE ; 
 int LSM_APPLIST_SZ ; 
 int LSM_MAX_BLOCK_REDIRECTS ; 
 int LSM_OK ; 
 int ckptLoadLevels (TYPE_5__*,void**,int*,int,TYPE_7__**) ; 
 int /*<<< orphan*/  ckptRead64 (void**) ; 
 int /*<<< orphan*/  lsmCheckpointId (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmCheckpointLogOffset (void**) ; 
 int /*<<< orphan*/  lsmFreeSnapshot (int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_9__* lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 

int lsmCheckpointDeserialize(
  lsm_db *pDb, 
  int bInclFreelist,              /* If true, deserialize free-list */
  u32 *aCkpt, 
  Snapshot **ppSnap
){
  int rc = LSM_OK;
  Snapshot *pNew;

  pNew = (Snapshot *)lsmMallocZeroRc(pDb->pEnv, sizeof(Snapshot), &rc);
  if( rc==LSM_OK ){
    Level *pLvl;
    int nFree;
    int i;
    int nLevel = (int)aCkpt[CKPT_HDR_NLEVEL];
    int iIn = CKPT_HDR_SIZE + CKPT_APPENDLIST_SIZE + CKPT_LOGPTR_SIZE;

    pNew->iId = lsmCheckpointId(aCkpt, 0);
    pNew->nBlock = aCkpt[CKPT_HDR_NBLOCK];
    pNew->nWrite = aCkpt[CKPT_HDR_NWRITE];
    rc = ckptLoadLevels(pDb, aCkpt, &iIn, nLevel, &pNew->pLevel);
    pNew->iLogOff = lsmCheckpointLogOffset(aCkpt);
    pNew->iCmpId = aCkpt[CKPT_HDR_CMPID];

    /* Make a copy of the append-list */
    for(i=0; i<LSM_APPLIST_SZ; i++){
      u32 *a = &aCkpt[CKPT_HDR_SIZE + CKPT_LOGPTR_SIZE + i*2];
      pNew->aiAppend[i] = ckptRead64(a);
    }

    /* Read the block-redirect list */
    pNew->redirect.n = aCkpt[iIn++];
    if( pNew->redirect.n ){
      pNew->redirect.a = lsmMallocZeroRc(pDb->pEnv, 
          (sizeof(struct RedirectEntry) * LSM_MAX_BLOCK_REDIRECTS), &rc
      );
      if( rc==LSM_OK ){
        for(i=0; i<pNew->redirect.n; i++){
          pNew->redirect.a[i].iFrom = aCkpt[iIn++];
          pNew->redirect.a[i].iTo = aCkpt[iIn++];
        }
      }
      for(pLvl=pNew->pLevel; pLvl->pNext; pLvl=pLvl->pNext);
      if( pLvl->nRight ){
        pLvl->aRhs[pLvl->nRight-1].pRedirect = &pNew->redirect;
      }else{
        pLvl->lhs.pRedirect = &pNew->redirect;
      }
    }

    /* Copy the free-list */
    if( rc==LSM_OK && bInclFreelist ){
      nFree = aCkpt[iIn++];
      if( nFree ){
        pNew->freelist.aEntry = (FreelistEntry *)lsmMallocZeroRc(
            pDb->pEnv, sizeof(FreelistEntry)*nFree, &rc
        );
        if( rc==LSM_OK ){
          int j;
          for(j=0; j<nFree; j++){
            FreelistEntry *p = &pNew->freelist.aEntry[j];
            p->iBlk = aCkpt[iIn++];
            p->iId = ((i64)(aCkpt[iIn])<<32) + aCkpt[iIn+1];
            iIn += 2;
          }
          pNew->freelist.nEntry = pNew->freelist.nAlloc = nFree;
        }
      }
    }
  }

  if( rc!=LSM_OK ){
    lsmFreeSnapshot(pDb->pEnv, pNew);
    pNew = 0;
  }

  *ppSnap = pNew;
  return rc;
}