#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_12__ {TYPE_2__* aReadr; } ;
struct TYPE_11__ {int /*<<< orphan*/  iEof; } ;
struct TYPE_10__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ SortSubtask ;
typedef  TYPE_2__ PmaReader ;
typedef  TYPE_3__ MergeEngine ;

/* Variables and functions */
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  vdbeMergeEngineFree (TYPE_3__*) ; 
 TYPE_3__* vdbeMergeEngineNew (int) ; 
 int vdbePmaReaderInit (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vdbeMergeEngineLevel0(
  SortSubtask *pTask,             /* Sorter task to read from */
  int nPMA,                       /* Number of PMAs to read */
  i64 *piOffset,                  /* IN/OUT: Readr offset in pTask->file */
  MergeEngine **ppOut             /* OUT: New merge-engine */
){
  MergeEngine *pNew;              /* Merge engine to return */
  i64 iOff = *piOffset;
  int i;
  int rc = SQLITE_OK;

  *ppOut = pNew = vdbeMergeEngineNew(nPMA);
  if( pNew==0 ) rc = SQLITE_NOMEM_BKPT;

  for(i=0; i<nPMA && rc==SQLITE_OK; i++){
    i64 nDummy = 0;
    PmaReader *pReadr = &pNew->aReadr[i];
    rc = vdbePmaReaderInit(pTask, &pTask->file, iOff, pReadr, &nDummy);
    iOff = pReadr->iEof;
  }

  if( rc!=SQLITE_OK ){
    vdbeMergeEngineFree(pNew);
    *ppOut = 0;
  }
  *piOffset = iOff;
  return rc;
}