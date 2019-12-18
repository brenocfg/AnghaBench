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
typedef  int u32 ;
struct TYPE_6__ {TYPE_1__* pShmhdr; } ;
typedef  TYPE_2__ lsm_db ;
typedef  int i64 ;
struct TYPE_5__ {int* aSnap1; } ;

/* Variables and functions */
 size_t CKPT_HDR_NWRITE ; 
 size_t CKPT_HDR_PGSZ ; 
 int LSM_OK ; 
 int lsmCheckpointSynced (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int lsmCheckpointSize(lsm_db *db, int *pnKB){
  int rc = LSM_OK;
  u32 nSynced;

  /* Set nSynced to the number of pages that had been written when the 
  ** database was last checkpointed. */
  rc = lsmCheckpointSynced(db, 0, 0, &nSynced);

  if( rc==LSM_OK ){
    u32 nPgsz = db->pShmhdr->aSnap1[CKPT_HDR_PGSZ];
    u32 nWrite = db->pShmhdr->aSnap1[CKPT_HDR_NWRITE];
    *pnKB = (int)(( ((i64)(nWrite - nSynced) * nPgsz) + 1023) / 1024);
  }

  return rc;
}