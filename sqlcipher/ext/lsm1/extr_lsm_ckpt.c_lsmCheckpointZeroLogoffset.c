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
typedef  size_t u32 ;
struct TYPE_5__ {size_t* aSnapshot; TYPE_1__* pShmhdr; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_4__ {size_t* aSnap1; size_t* aSnap2; } ;

/* Variables and functions */
 size_t CKPT_HDR_LO_LSW ; 
 size_t CKPT_HDR_LO_MSW ; 
 size_t CKPT_HDR_NCKPT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ckptChecksum (size_t*,size_t,size_t*,size_t*) ; 
 scalar_t__ memcmp (size_t*,size_t*,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,size_t) ; 

void lsmCheckpointZeroLogoffset(lsm_db *pDb){
  u32 nCkpt;

  nCkpt = pDb->aSnapshot[CKPT_HDR_NCKPT];
  assert( nCkpt>CKPT_HDR_NCKPT );
  assert( nCkpt==pDb->pShmhdr->aSnap1[CKPT_HDR_NCKPT] );
  assert( 0==memcmp(pDb->aSnapshot, pDb->pShmhdr->aSnap1, nCkpt*sizeof(u32)) );
  assert( 0==memcmp(pDb->aSnapshot, pDb->pShmhdr->aSnap2, nCkpt*sizeof(u32)) );

  pDb->aSnapshot[CKPT_HDR_LO_MSW] = 0;
  pDb->aSnapshot[CKPT_HDR_LO_LSW] = 0;
  ckptChecksum(pDb->aSnapshot, nCkpt, 
      &pDb->aSnapshot[nCkpt-2], &pDb->aSnapshot[nCkpt-1]
  );

  memcpy(pDb->pShmhdr->aSnap1, pDb->aSnapshot, nCkpt*sizeof(u32));
  memcpy(pDb->pShmhdr->aSnap2, pDb->aSnapshot, nCkpt*sizeof(u32));
}