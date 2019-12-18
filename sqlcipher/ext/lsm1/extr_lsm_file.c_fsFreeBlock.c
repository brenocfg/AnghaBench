#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  pDb; } ;
struct TYPE_12__ {struct TYPE_12__* pNext; } ;
struct TYPE_11__ {scalar_t__* aiAppend; } ;
typedef  TYPE_1__ Snapshot ;
typedef  int /*<<< orphan*/  Segment ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_2__ Level ;
typedef  TYPE_3__ FileSystem ;

/* Variables and functions */
 int LSM_APPLIST_SZ ; 
 int LSM_OK ; 
 scalar_t__ fsFirstPageOnBlock (TYPE_3__*,int) ; 
 scalar_t__ fsLastPageOnBlock (TYPE_3__*,int) ; 
 scalar_t__ fsLevelEndsBetween (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int lsmBlockFree (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* lsmDbSnapshotLevel (TYPE_1__*) ; 

__attribute__((used)) static int fsFreeBlock(
  FileSystem *pFS,                /* File system object */
  Snapshot *pSnapshot,            /* Worker snapshot */
  Segment *pIgnore,               /* Ignore this run when searching */
  int iBlk                        /* Block number of block to free */
){
  int rc = LSM_OK;                /* Return code */
  LsmPgno iFirst;                 /* First page on block iBlk */
  LsmPgno iLast;                  /* Last page on block iBlk */
  Level *pLevel;                  /* Used to iterate through levels */

  int iIn;                        /* Used to iterate through append points */
  int iOut = 0;                   /* Used to output append points */
  LsmPgno *aApp = pSnapshot->aiAppend;

  iFirst = fsFirstPageOnBlock(pFS, iBlk);
  iLast = fsLastPageOnBlock(pFS, iBlk);

  /* Check if any other run in the snapshot has a start or end page 
  ** within this block. If there is such a run, return early. */
  for(pLevel=lsmDbSnapshotLevel(pSnapshot); pLevel; pLevel=pLevel->pNext){
    if( fsLevelEndsBetween(pLevel, pIgnore, iFirst, iLast) ){
      return LSM_OK;
    }
  }

  /* Remove any entries that lie on this block from the append-list. */
  for(iIn=0; iIn<LSM_APPLIST_SZ; iIn++){
    if( aApp[iIn]<iFirst || aApp[iIn]>iLast ){
      aApp[iOut++] = aApp[iIn];
    }
  }
  while( iOut<LSM_APPLIST_SZ ) aApp[iOut++] = 0;

  if( rc==LSM_OK ){
    rc = lsmBlockFree(pFS->pDb, iBlk);
  }
  return rc;
}