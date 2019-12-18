#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_13__ {int /*<<< orphan*/  pFS; int /*<<< orphan*/ * pEnv; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_16__ {int iSplitTopic; void* pSplitKey; int /*<<< orphan*/  nSplitKey; TYPE_3__* pMerge; } ;
struct TYPE_15__ {void* pData; int /*<<< orphan*/  nData; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int /*<<< orphan*/  iCell; int /*<<< orphan*/  iPg; } ;
struct TYPE_14__ {TYPE_1__ splitkey; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_3__ Merge ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  TYPE_4__ LsmBlob ;
typedef  TYPE_5__ Level ;

/* Variables and functions */
 int LSM_OK ; 
 int SEGMENT_BTREE_FLAG ; 
 int lsmFsDbPageGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * lsmFsPageData (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int pageGetBtreeKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,void**,int*,TYPE_4__*) ; 
 int pageGetFlags (int /*<<< orphan*/ *,int) ; 
 int pageGetKeyCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,TYPE_4__*) ; 
 int sortedBlobSet (int /*<<< orphan*/ *,TYPE_4__*,void*,int) ; 
 int /*<<< orphan*/ * sortedSplitkeySegment (TYPE_5__*) ; 

__attribute__((used)) static void sortedSplitkey(lsm_db *pDb, Level *pLevel, int *pRc){
  Segment *pSeg;
  Page *pPg = 0;
  lsm_env *pEnv = pDb->pEnv;      /* Environment handle */
  int rc = *pRc;
  Merge *pMerge = pLevel->pMerge;

  pSeg = sortedSplitkeySegment(pLevel);
  if( rc==LSM_OK ){
    rc = lsmFsDbPageGet(pDb->pFS, pSeg, pMerge->splitkey.iPg, &pPg);
  }
  if( rc==LSM_OK ){
    int iTopic;
    LsmBlob blob = {0, 0, 0, 0};
    u8 *aData;
    int nData;
  
    aData = lsmFsPageData(pPg, &nData);
    if( pageGetFlags(aData, nData) & SEGMENT_BTREE_FLAG ){
      void *pKey;
      int nKey;
      LsmPgno dummy;
      rc = pageGetBtreeKey(pSeg,
          pPg, pMerge->splitkey.iCell, &dummy, &iTopic, &pKey, &nKey, &blob
      );
      if( rc==LSM_OK && blob.pData!=pKey ){
        rc = sortedBlobSet(pEnv, &blob, pKey, nKey);
      }
    }else{
      rc = pageGetKeyCopy(
          pEnv, pSeg, pPg, pMerge->splitkey.iCell, &iTopic, &blob
      );
    }

    pLevel->iSplitTopic = iTopic;
    pLevel->pSplitKey = blob.pData;
    pLevel->nSplitKey = blob.nData;
    lsmFsPageRelease(pPg);
  }

  *pRc = rc;
}