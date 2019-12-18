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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * aFrameCksum; int /*<<< orphan*/  mxFrame; } ;
struct TYPE_5__ {int /*<<< orphan*/  nCkpt; TYPE_1__ hdr; int /*<<< orphan*/  writeLock; } ;
typedef  TYPE_2__ Wal ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void sqlite3WalSavepoint(Wal *pWal, u32 *aWalData){
  assert( pWal->writeLock );
  aWalData[0] = pWal->hdr.mxFrame;
  aWalData[1] = pWal->hdr.aFrameCksum[0];
  aWalData[2] = pWal->hdr.aFrameCksum[1];
  aWalData[3] = pWal->nCkpt;
}