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
typedef  int u32 ;
struct TYPE_4__ {int nDfltBlksz; int nDfltPgsz; int /*<<< orphan*/  aSnapshot; TYPE_2__* pShmhdr; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_5__ {int /*<<< orphan*/  aSnap2; int /*<<< orphan*/  aSnap1; } ;
typedef  TYPE_2__ ShmHeader ;

/* Variables and functions */
 size_t CKPT_HDR_BLKSZ ; 
 size_t CKPT_HDR_NCKPT ; 
 size_t CKPT_HDR_PGSZ ; 
 int LSM_COMPRESSION_EMPTY ; 
 int array_size (int*) ; 
 int /*<<< orphan*/  ckptChecksum (int*,int,int*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void ckptLoadEmpty(lsm_db *pDb){
  u32 aCkpt[] = {
    0,                       /* CKPT_HDR_ID_MSW */
    10,                      /* CKPT_HDR_ID_LSW */
    0,                       /* CKPT_HDR_NCKPT */
    LSM_COMPRESSION_EMPTY,   /* CKPT_HDR_CMPID */
    0,                       /* CKPT_HDR_NBLOCK */
    0,                       /* CKPT_HDR_BLKSZ */
    0,                       /* CKPT_HDR_NLEVEL */
    0,                       /* CKPT_HDR_PGSZ */
    0,                       /* CKPT_HDR_NWRITE */
    0, 0, 1234, 5678,        /* The log pointer and initial checksum */
    0,0,0,0, 0,0,0,0,        /* The append list */
    0,                       /* The redirected block list */
    0,                       /* The free block list */
    0, 0                     /* Space for checksum values */
  };
  u32 nCkpt = array_size(aCkpt);
  ShmHeader *pShm = pDb->pShmhdr;

  aCkpt[CKPT_HDR_NCKPT] = nCkpt;
  aCkpt[CKPT_HDR_BLKSZ] = pDb->nDfltBlksz;
  aCkpt[CKPT_HDR_PGSZ] = pDb->nDfltPgsz;
  ckptChecksum(aCkpt, array_size(aCkpt), &aCkpt[nCkpt-2], &aCkpt[nCkpt-1]);

  memcpy(pShm->aSnap1, aCkpt, nCkpt*sizeof(u32));
  memcpy(pShm->aSnap2, aCkpt, nCkpt*sizeof(u32));
  memcpy(pDb->aSnapshot, aCkpt, nCkpt*sizeof(u32));
}