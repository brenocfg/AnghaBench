#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {scalar_t__ aMemory; scalar_t__ szPMA; scalar_t__ pList; } ;
struct TYPE_8__ {scalar_t__ pReader; int nTask; scalar_t__ pUnpacked; scalar_t__ mxKeysize; scalar_t__ iMemory; scalar_t__ bUsePMA; TYPE_1__ list; TYPE_3__* aTask; scalar_t__ pMerger; scalar_t__ bUseThreads; } ;
typedef  TYPE_2__ VdbeSorter ;
struct TYPE_9__ {TYPE_2__* pSorter; } ;
typedef  TYPE_3__ SortSubtask ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vdbeMergeEngineFree (scalar_t__) ; 
 int /*<<< orphan*/  vdbePmaReaderClear (scalar_t__) ; 
 int /*<<< orphan*/  vdbeSortSubtaskCleanup (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  vdbeSorterJoinAll (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdbeSorterRecordFree (int /*<<< orphan*/ ,scalar_t__) ; 

void sqlite3VdbeSorterReset(sqlite3 *db, VdbeSorter *pSorter){
  int i;
  (void)vdbeSorterJoinAll(pSorter, SQLITE_OK);
  assert( pSorter->bUseThreads || pSorter->pReader==0 );
#if SQLITE_MAX_WORKER_THREADS>0
  if( pSorter->pReader ){
    vdbePmaReaderClear(pSorter->pReader);
    sqlite3DbFree(db, pSorter->pReader);
    pSorter->pReader = 0;
  }
#endif
  vdbeMergeEngineFree(pSorter->pMerger);
  pSorter->pMerger = 0;
  for(i=0; i<pSorter->nTask; i++){
    SortSubtask *pTask = &pSorter->aTask[i];
    vdbeSortSubtaskCleanup(db, pTask);
    pTask->pSorter = pSorter;
  }
  if( pSorter->list.aMemory==0 ){
    vdbeSorterRecordFree(0, pSorter->list.pList);
  }
  pSorter->list.pList = 0;
  pSorter->list.szPMA = 0;
  pSorter->bUsePMA = 0;
  pSorter->iMemory = 0;
  pSorter->mxKeysize = 0;
  sqlite3DbFree(db, pSorter->pUnpacked);
  pSorter->pUnpacked = 0;
}