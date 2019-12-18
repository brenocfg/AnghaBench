#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * pWorker; int /*<<< orphan*/ * pFS; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_10__ {scalar_t__ nSize; scalar_t__ iFirst; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__ Segment ;
typedef  scalar_t__ LsmPgno ;
typedef  int /*<<< orphan*/  FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ firstOnBlock (int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 int fsBlockNext (int /*<<< orphan*/ *,TYPE_2__*,int,int*) ; 
 scalar_t__ fsFirstPageOnBlock (int /*<<< orphan*/ *,int) ; 
 int fsFreeBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ fsLastPageOnBlock (int /*<<< orphan*/ *,int) ; 
 scalar_t__ fsPageRedirects (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 int fsPageToBlock (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ fsSegmentRedirects (int /*<<< orphan*/ *,TYPE_2__*) ; 

void lsmFsGobble(
  lsm_db *pDb,
  Segment *pRun, 
  LsmPgno *aPgno,
  int nPgno
){
  int rc = LSM_OK;
  FileSystem *pFS = pDb->pFS;
  Snapshot *pSnapshot = pDb->pWorker;
  int iBlk;

  assert( pRun->nSize>0 );
  assert( 0==fsSegmentRedirects(pFS, pRun) );
  assert( nPgno>0 && 0==fsPageRedirects(pFS, pRun, aPgno[0]) );

  iBlk = fsPageToBlock(pFS, pRun->iFirst);
  pRun->nSize += (int)(pRun->iFirst - fsFirstPageOnBlock(pFS, iBlk));

  while( rc==LSM_OK ){
    int iNext = 0;
    LsmPgno iFirst = firstOnBlock(pFS, iBlk, aPgno, nPgno);
    if( iFirst ){
      pRun->iFirst = iFirst;
      break;
    }
    rc = fsBlockNext(pFS, pRun, iBlk, &iNext);
    if( rc==LSM_OK ) rc = fsFreeBlock(pFS, pSnapshot, pRun, iBlk);
    pRun->nSize -= (int)(
        1 + fsLastPageOnBlock(pFS, iBlk) - fsFirstPageOnBlock(pFS, iBlk)
    );
    iBlk = iNext;
  }

  pRun->nSize -= (int)(pRun->iFirst - fsFirstPageOnBlock(pFS, iBlk));
  assert( pRun->nSize>0 );
}