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
typedef  void* u32 ;
struct TYPE_5__ {int /*<<< orphan*/  iSnapshotId; void* cksum1; void* cksum0; TYPE_1__* aRegion; } ;
struct TYPE_4__ {int iStart; } ;
typedef  TYPE_2__ DbLog ;

/* Variables and functions */
 size_t CKPT_HDR_LO_CKSUM1 ; 
 size_t CKPT_HDR_LO_CKSUM2 ; 
 int /*<<< orphan*/  lsmCheckpointId (void**,int /*<<< orphan*/ ) ; 
 int lsmCheckpointLogOffset (void**) ; 

void lsmCheckpointLogoffset(
  u32 *aCkpt,
  DbLog *pLog
){ 
  pLog->aRegion[2].iStart = (lsmCheckpointLogOffset(aCkpt) >> 1);

  pLog->cksum0 = aCkpt[CKPT_HDR_LO_CKSUM1];
  pLog->cksum1 = aCkpt[CKPT_HDR_LO_CKSUM2];
  pLog->iSnapshotId = lsmCheckpointId(aCkpt, 0);
}