#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;

/* Type definitions */
struct RedirectEntry {int dummy; } ;
struct TYPE_21__ {TYPE_3__* pWorker; int /*<<< orphan*/  pFS; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_25__ {int iTo; int iFrom; } ;
struct TYPE_19__ {TYPE_1__* pRedirect; } ;
struct TYPE_24__ {scalar_t__ pNext; scalar_t__ nRight; TYPE_14__ lhs; } ;
struct TYPE_23__ {int iFrom; scalar_t__ iSeen; } ;
struct TYPE_20__ {int n; TYPE_7__* a; } ;
struct TYPE_22__ {TYPE_1__ redirect; scalar_t__ nBlock; } ;
typedef  TYPE_3__ Snapshot ;
typedef  TYPE_4__ MoveBlockCtx ;
typedef  TYPE_5__ Level ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_LOG_DATA ; 
 int LSM_MAX_BLOCK_REDIRECTS ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmBlockAllocate (TYPE_2__*,int,int*) ; 
 int lsmBlockFree (TYPE_2__*,int) ; 
 TYPE_5__* lsmDbSnapshotLevel (TYPE_3__*) ; 
 int lsmFsBlockSize (int /*<<< orphan*/ ) ; 
 int lsmFsMoveBlock (int /*<<< orphan*/ ,TYPE_14__*,int,int) ; 
 int lsmFsPageSize (int /*<<< orphan*/ ) ; 
 TYPE_7__* lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  lsmSortedDumpStructure (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int lsmWalkFreelist (TYPE_2__*,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  memmove (TYPE_7__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  moveBlockCb ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static int sortedMoveBlock(lsm_db *pDb, int *pnWrite){
  Snapshot *p = pDb->pWorker;
  Level *pLvl = lsmDbSnapshotLevel(p);
  int iFrom;                      /* Block to move */
  int iTo;                        /* Destination to move block to */
  int rc;                         /* Return code */

  MoveBlockCtx sCtx;

  assert( pLvl->pNext==0 && pLvl->nRight==0 );
  assert( p->redirect.n<=LSM_MAX_BLOCK_REDIRECTS );

  *pnWrite = 0;

  /* Check that the redirect array is not already full. If it is, return
  ** without moving any database content.  */
  if( p->redirect.n>=LSM_MAX_BLOCK_REDIRECTS ) return LSM_OK;

  /* Find the last block of content in the database file. Do this by 
  ** traversing the free-list in reverse (descending block number) order.
  ** The first block not on the free list is the one that will be moved.
  ** Since the db consists of a single segment, there is no ambiguity as
  ** to which segment the block belongs to.  */
  sCtx.iSeen = p->nBlock+1;
  sCtx.iFrom = 0;
  rc = lsmWalkFreelist(pDb, 1, moveBlockCb, &sCtx);
  if( rc!=LSM_OK || sCtx.iFrom==0 ) return rc;
  iFrom = sCtx.iFrom;

  /* Find the first free block in the database, ignoring block 1. Block
  ** 1 is tricky as it is smaller than the other blocks.  */
  rc = lsmBlockAllocate(pDb, iFrom, &iTo);
  if( rc!=LSM_OK || iTo==0 ) return rc;
  assert( iTo!=1 && iTo<iFrom );

  rc = lsmFsMoveBlock(pDb->pFS, &pLvl->lhs, iTo, iFrom);
  if( rc==LSM_OK ){
    if( p->redirect.a==0 ){
      int nByte = sizeof(struct RedirectEntry) * LSM_MAX_BLOCK_REDIRECTS;
      p->redirect.a = lsmMallocZeroRc(pDb->pEnv, nByte, &rc);
    }
    if( rc==LSM_OK ){

      /* Check if the block just moved was already redirected. */
      int i;
      for(i=0; i<p->redirect.n; i++){
        if( p->redirect.a[i].iTo==iFrom ) break;
      }

      if( i==p->redirect.n ){
        /* Block iFrom was not already redirected. Add a new array entry. */
        memmove(&p->redirect.a[1], &p->redirect.a[0], 
            sizeof(struct RedirectEntry) * p->redirect.n
            );
        p->redirect.a[0].iFrom = iFrom;
        p->redirect.a[0].iTo = iTo;
        p->redirect.n++;
      }else{
        /* Block iFrom was already redirected. Overwrite existing entry. */
        p->redirect.a[i].iTo = iTo;
      }

      rc = lsmBlockFree(pDb, iFrom);

      *pnWrite = lsmFsBlockSize(pDb->pFS) / lsmFsPageSize(pDb->pFS);
      pLvl->lhs.pRedirect = &p->redirect;
    }
  }

#if LSM_LOG_STRUCTURE
  if( rc==LSM_OK ){
    char aBuf[64];
    sprintf(aBuf, "move-block %d/%d", p->redirect.n-1, LSM_MAX_BLOCK_REDIRECTS);
    lsmSortedDumpStructure(pDb, pDb->pWorker, LSM_LOG_DATA, 0, aBuf);
  }
#endif
  return rc;
}