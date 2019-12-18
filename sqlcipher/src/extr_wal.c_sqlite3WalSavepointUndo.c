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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ mxFrame; scalar_t__* aFrameCksum; } ;
struct TYPE_6__ {int writeLock; scalar_t__ nCkpt; TYPE_1__ hdr; } ;
typedef  TYPE_2__ Wal ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  walCleanupHash (TYPE_2__*) ; 

int sqlite3WalSavepointUndo(Wal *pWal, u32 *aWalData){
  int rc = SQLITE_OK;

  assert( pWal->writeLock );
  assert( aWalData[3]!=pWal->nCkpt || aWalData[0]<=pWal->hdr.mxFrame );

  if( aWalData[3]!=pWal->nCkpt ){
    /* This savepoint was opened immediately after the write-transaction
    ** was started. Right after that, the writer decided to wrap around
    ** to the start of the log. Update the savepoint values to match.
    */
    aWalData[0] = 0;
    aWalData[3] = pWal->nCkpt;
  }

  if( aWalData[0]<pWal->hdr.mxFrame ){
    pWal->hdr.mxFrame = aWalData[0];
    pWal->hdr.aFrameCksum[0] = aWalData[1];
    pWal->hdr.aFrameCksum[1] = aWalData[2];
    walCleanupHash(pWal);
  }

  return rc;
}