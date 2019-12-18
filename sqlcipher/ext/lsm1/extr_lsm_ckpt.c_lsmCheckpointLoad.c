#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  aSnapshot; TYPE_2__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_6__ {int* aSnap1; int* aSnap2; } ;
typedef  TYPE_2__ ShmHeader ;

/* Variables and functions */
 size_t CKPT_HDR_NCKPT ; 
 int LSM_ATTEMPTS_BEFORE_PROTOCOL ; 
 int LSM_META_RW_PAGE_SIZE ; 
 int LSM_OK ; 
 int LSM_PROTOCOL_BKPT ; 
 scalar_t__ ckptChecksumOk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmShmBarrier (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

int lsmCheckpointLoad(lsm_db *pDb, int *piRead){
  int nRem = LSM_ATTEMPTS_BEFORE_PROTOCOL;
  ShmHeader *pShm = pDb->pShmhdr;
  while( (nRem--)>0 ){
    int nInt;

    nInt = pShm->aSnap1[CKPT_HDR_NCKPT];
    if( nInt<=(LSM_META_RW_PAGE_SIZE / sizeof(u32)) ){
      memcpy(pDb->aSnapshot, pShm->aSnap1, nInt*sizeof(u32));
      if( ckptChecksumOk(pDb->aSnapshot) ){
        if( piRead ) *piRead = 1;
        return LSM_OK;
      }
    }

    nInt = pShm->aSnap2[CKPT_HDR_NCKPT];
    if( nInt<=(LSM_META_RW_PAGE_SIZE / sizeof(u32)) ){
      memcpy(pDb->aSnapshot, pShm->aSnap2, nInt*sizeof(u32));
      if( ckptChecksumOk(pDb->aSnapshot) ){
        if( piRead ) *piRead = 2;
        return LSM_OK;
      }
    }

    lsmShmBarrier(pDb);
  }
  return LSM_PROTOCOL_BKPT;
}