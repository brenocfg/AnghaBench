#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_16__ {scalar_t__ pFd; scalar_t__ iEof; } ;
struct TYPE_19__ {scalar_t__ nPMA; TYPE_3__ file; TYPE_1__* pSorter; } ;
struct TYPE_18__ {scalar_t__ szPMA; scalar_t__ aMemory; scalar_t__ pList; } ;
struct TYPE_15__ {TYPE_4__* pNext; } ;
struct TYPE_17__ {scalar_t__ nVal; TYPE_2__ u; } ;
struct TYPE_14__ {int /*<<< orphan*/  pgsz; int /*<<< orphan*/ * db; } ;
typedef  TYPE_4__ SorterRecord ;
typedef  TYPE_5__ SorterList ;
typedef  TYPE_6__ SortSubtask ;
typedef  int /*<<< orphan*/  PmaWriter ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SRVAL (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ iSz ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_4__*) ; 
 int /*<<< orphan*/  vdbePmaWriteBlob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vdbePmaWriteVarint (int /*<<< orphan*/ *,scalar_t__) ; 
 int vdbePmaWriterFinish (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  vdbePmaWriterInit (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vdbeSorterExtendFile (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int vdbeSorterOpenTempFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int vdbeSorterSort (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  vdbeSorterWorkDebug (TYPE_6__*,char*) ; 

__attribute__((used)) static int vdbeSorterListToPMA(SortSubtask *pTask, SorterList *pList){
  sqlite3 *db = pTask->pSorter->db;
  int rc = SQLITE_OK;             /* Return code */
  PmaWriter writer;               /* Object used to write to the file */

#ifdef SQLITE_DEBUG
  /* Set iSz to the expected size of file pTask->file after writing the PMA. 
  ** This is used by an assert() statement at the end of this function.  */
  i64 iSz = pList->szPMA + sqlite3VarintLen(pList->szPMA) + pTask->file.iEof;
#endif

  vdbeSorterWorkDebug(pTask, "enter");
  memset(&writer, 0, sizeof(PmaWriter));
  assert( pList->szPMA>0 );

  /* If the first temporary PMA file has not been opened, open it now. */
  if( pTask->file.pFd==0 ){
    rc = vdbeSorterOpenTempFile(db, 0, &pTask->file.pFd);
    assert( rc!=SQLITE_OK || pTask->file.pFd );
    assert( pTask->file.iEof==0 );
    assert( pTask->nPMA==0 );
  }

  /* Try to get the file to memory map */
  if( rc==SQLITE_OK ){
    vdbeSorterExtendFile(db, pTask->file.pFd, pTask->file.iEof+pList->szPMA+9);
  }

  /* Sort the list */
  if( rc==SQLITE_OK ){
    rc = vdbeSorterSort(pTask, pList);
  }

  if( rc==SQLITE_OK ){
    SorterRecord *p;
    SorterRecord *pNext = 0;

    vdbePmaWriterInit(pTask->file.pFd, &writer, pTask->pSorter->pgsz,
                      pTask->file.iEof);
    pTask->nPMA++;
    vdbePmaWriteVarint(&writer, pList->szPMA);
    for(p=pList->pList; p; p=pNext){
      pNext = p->u.pNext;
      vdbePmaWriteVarint(&writer, p->nVal);
      vdbePmaWriteBlob(&writer, SRVAL(p), p->nVal);
      if( pList->aMemory==0 ) sqlite3_free(p);
    }
    pList->pList = p;
    rc = vdbePmaWriterFinish(&writer, &pTask->file.iEof);
  }

  vdbeSorterWorkDebug(pTask, "exit");
  assert( rc!=SQLITE_OK || pList->pList==0 );
  assert( rc!=SQLITE_OK || pTask->file.iEof==iSz );
  return rc;
}