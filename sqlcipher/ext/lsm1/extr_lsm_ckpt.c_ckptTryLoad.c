#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int* aSnapshot; int /*<<< orphan*/  pEnv; TYPE_2__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_5__ {int* aSnap1; int* aSnap2; int iMetaPage; } ;
typedef  TYPE_2__ ShmHeader ;
typedef  int /*<<< orphan*/  MetaPage ;

/* Variables and functions */
 int CKPT_HDR_NCKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  ckptChangeEndianness (int*,int) ; 
 scalar_t__ ckptChecksumOk (int*) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,int*) ; 
 int* lsmFsMetaPageData (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lsmGetU32 (int*) ; 
 scalar_t__ lsmMallocRc (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int ckptTryLoad(lsm_db *pDb, MetaPage *pPg, u32 iMeta, int *pRc){
  int bLoaded = 0;                /* Return value */
  if( *pRc==LSM_OK ){
    int rc = LSM_OK;              /* Error code */
    u32 *aCkpt = 0;               /* Pointer to buffer containing checkpoint */
    u32 nCkpt;                    /* Number of elements in aCkpt[] */
    int nData;                    /* Bytes of data in aData[] */
    u8 *aData;                    /* Meta page data */
   
    aData = lsmFsMetaPageData(pPg, &nData);
    nCkpt = (u32)lsmGetU32(&aData[CKPT_HDR_NCKPT*sizeof(u32)]);
    if( nCkpt<=nData/sizeof(u32) && nCkpt>CKPT_HDR_NCKPT ){
      aCkpt = (u32 *)lsmMallocRc(pDb->pEnv, nCkpt*sizeof(u32), &rc);
    }
    if( aCkpt ){
      memcpy(aCkpt, aData, nCkpt*sizeof(u32));
      ckptChangeEndianness(aCkpt, nCkpt);
      if( ckptChecksumOk(aCkpt) ){
        ShmHeader *pShm = pDb->pShmhdr;
        memcpy(pShm->aSnap1, aCkpt, nCkpt*sizeof(u32));
        memcpy(pShm->aSnap2, aCkpt, nCkpt*sizeof(u32));
        memcpy(pDb->aSnapshot, aCkpt, nCkpt*sizeof(u32));
        pShm->iMetaPage = iMeta;
        bLoaded = 1;
      }
    }

    lsmFree(pDb->pEnv, aCkpt);
    *pRc = rc;
  }
  return bLoaded;
}