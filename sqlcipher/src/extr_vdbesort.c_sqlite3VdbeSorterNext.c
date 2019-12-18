#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_13__ {scalar_t__ aMemory; TYPE_6__* pList; } ;
struct TYPE_14__ {int bUseThreads; TYPE_3__ list; TYPE_9__* pMerger; int /*<<< orphan*/ * aTask; TYPE_8__* pReader; scalar_t__ bUsePMA; } ;
typedef  TYPE_4__ VdbeSorter ;
struct TYPE_11__ {TYPE_4__* pSorter; } ;
struct TYPE_15__ {scalar_t__ eCurType; TYPE_1__ uc; } ;
typedef  TYPE_5__ VdbeCursor ;
struct TYPE_18__ {int /*<<< orphan*/ * pTask; } ;
struct TYPE_17__ {scalar_t__ pFd; } ;
struct TYPE_12__ {TYPE_6__* pNext; } ;
struct TYPE_16__ {TYPE_2__ u; } ;
typedef  TYPE_6__ SorterRecord ;

/* Variables and functions */
 scalar_t__ CURTYPE_SORTER ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int vdbeMergeEngineStep (TYPE_9__*,int*) ; 
 int vdbePmaReaderNext (TYPE_8__*) ; 
 int /*<<< orphan*/  vdbeSorterRecordFree (int /*<<< orphan*/ *,TYPE_6__*) ; 

int sqlite3VdbeSorterNext(sqlite3 *db, const VdbeCursor *pCsr){
  VdbeSorter *pSorter;
  int rc;                         /* Return code */

  assert( pCsr->eCurType==CURTYPE_SORTER );
  pSorter = pCsr->uc.pSorter;
  assert( pSorter->bUsePMA || (pSorter->pReader==0 && pSorter->pMerger==0) );
  if( pSorter->bUsePMA ){
    assert( pSorter->pReader==0 || pSorter->pMerger==0 );
    assert( pSorter->bUseThreads==0 || pSorter->pReader );
    assert( pSorter->bUseThreads==1 || pSorter->pMerger );
#if SQLITE_MAX_WORKER_THREADS>0
    if( pSorter->bUseThreads ){
      rc = vdbePmaReaderNext(pSorter->pReader);
      if( rc==SQLITE_OK && pSorter->pReader->pFd==0 ) rc = SQLITE_DONE;
    }else
#endif
    /*if( !pSorter->bUseThreads )*/ {
      int res = 0;
      assert( pSorter->pMerger!=0 );
      assert( pSorter->pMerger->pTask==(&pSorter->aTask[0]) );
      rc = vdbeMergeEngineStep(pSorter->pMerger, &res);
      if( rc==SQLITE_OK && res ) rc = SQLITE_DONE;
    }
  }else{
    SorterRecord *pFree = pSorter->list.pList;
    pSorter->list.pList = pFree->u.pNext;
    pFree->u.pNext = 0;
    if( pSorter->list.aMemory==0 ) vdbeSorterRecordFree(db, pFree);
    rc = pSorter->list.pList ? SQLITE_OK : SQLITE_DONE;
  }
  return rc;
}