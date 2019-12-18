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
struct TYPE_10__ {int /*<<< orphan*/  pDb; } ;
struct TYPE_9__ {scalar_t__ iLastPg; scalar_t__ pRedirect; int /*<<< orphan*/  nSize; } ;
typedef  TYPE_1__ Segment ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fsBlockNext (TYPE_2__*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ fsFirstPageOnBlock (TYPE_2__*,int) ; 
 scalar_t__ fsIsLast (TYPE_2__*,scalar_t__) ; 
 int fsPageToBlock (TYPE_2__*,scalar_t__) ; 
 int lsmBlockAllocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fsAppendPage(
  FileSystem *pFS, 
  Segment *pSeg,
  LsmPgno *piNew,
  int *piPrev,
  int *piNext
){
  LsmPgno iPrev = pSeg->iLastPg;
  int rc;
  assert( iPrev!=0 );

  *piPrev = 0;
  *piNext = 0;

  if( fsIsLast(pFS, iPrev) ){
    /* Grab the first page on the next block (which has already be
    ** allocated). In this case set *piPrev to tell the caller to set
    ** the "previous block" pointer in the first 4 bytes of the page.
    */
    int iNext;
    int iBlk = fsPageToBlock(pFS, iPrev);
    assert( pSeg->pRedirect==0 );
    rc = fsBlockNext(pFS, 0, iBlk, &iNext);
    if( rc!=LSM_OK ) return rc;
    *piNew = fsFirstPageOnBlock(pFS, iNext);
    *piPrev = iBlk;
  }else{
    *piNew = iPrev+1;
    if( fsIsLast(pFS, *piNew) ){
      /* Allocate the next block here. */
      int iBlk;
      rc = lsmBlockAllocate(pFS->pDb, 0, &iBlk);
      if( rc!=LSM_OK ) return rc;
      *piNext = iBlk;
    }
  }

  pSeg->nSize++;
  pSeg->iLastPg = *piNew;
  return LSM_OK;
}