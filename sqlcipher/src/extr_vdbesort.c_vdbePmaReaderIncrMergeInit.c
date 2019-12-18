#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_16__ {int mxSz; int iStartOff; scalar_t__ bUseThread; TYPE_2__* aFile; int /*<<< orphan*/  pMerger; TYPE_4__* pTask; } ;
struct TYPE_15__ {TYPE_6__* pIncr; } ;
struct TYPE_13__ {scalar_t__ pFd; int iEof; } ;
struct TYPE_14__ {TYPE_3__ file2; TYPE_1__* pSorter; } ;
struct TYPE_12__ {scalar_t__ pFd; } ;
struct TYPE_11__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_4__ SortSubtask ;
typedef  TYPE_5__ PmaReader ;
typedef  TYPE_6__ IncrMerger ;

/* Variables and functions */
 int INCRINIT_NORMAL ; 
 int INCRINIT_ROOT ; 
 int INCRINIT_TASK ; 
 scalar_t__ SQLITE_MAX_WORKER_THREADS ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int vdbeIncrPopulate (TYPE_6__*) ; 
 int vdbeMergeEngineInit (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int vdbePmaReaderNext (TYPE_5__*) ; 
 int vdbeSorterOpenTempFile (int /*<<< orphan*/ *,int,scalar_t__*) ; 

__attribute__((used)) static int vdbePmaReaderIncrMergeInit(PmaReader *pReadr, int eMode){
  int rc = SQLITE_OK;
  IncrMerger *pIncr = pReadr->pIncr;
  SortSubtask *pTask = pIncr->pTask;
  sqlite3 *db = pTask->pSorter->db;

  /* eMode is always INCRINIT_NORMAL in single-threaded mode */
  assert( SQLITE_MAX_WORKER_THREADS>0 || eMode==INCRINIT_NORMAL );

  rc = vdbeMergeEngineInit(pTask, pIncr->pMerger, eMode);

  /* Set up the required files for pIncr. A multi-theaded IncrMerge object
  ** requires two temp files to itself, whereas a single-threaded object
  ** only requires a region of pTask->file2. */
  if( rc==SQLITE_OK ){
    int mxSz = pIncr->mxSz;
#if SQLITE_MAX_WORKER_THREADS>0
    if( pIncr->bUseThread ){
      rc = vdbeSorterOpenTempFile(db, mxSz, &pIncr->aFile[0].pFd);
      if( rc==SQLITE_OK ){
        rc = vdbeSorterOpenTempFile(db, mxSz, &pIncr->aFile[1].pFd);
      }
    }else
#endif
    /*if( !pIncr->bUseThread )*/{
      if( pTask->file2.pFd==0 ){
        assert( pTask->file2.iEof>0 );
        rc = vdbeSorterOpenTempFile(db, pTask->file2.iEof, &pTask->file2.pFd);
        pTask->file2.iEof = 0;
      }
      if( rc==SQLITE_OK ){
        pIncr->aFile[1].pFd = pTask->file2.pFd;
        pIncr->iStartOff = pTask->file2.iEof;
        pTask->file2.iEof += mxSz;
      }
    }
  }

#if SQLITE_MAX_WORKER_THREADS>0
  if( rc==SQLITE_OK && pIncr->bUseThread ){
    /* Use the current thread to populate aFile[1], even though this
    ** PmaReader is multi-threaded. If this is an INCRINIT_TASK object,
    ** then this function is already running in background thread 
    ** pIncr->pTask->thread. 
    **
    ** If this is the INCRINIT_ROOT object, then it is running in the 
    ** main VDBE thread. But that is Ok, as that thread cannot return
    ** control to the VDBE or proceed with anything useful until the 
    ** first results are ready from this merger object anyway.
    */
    assert( eMode==INCRINIT_ROOT || eMode==INCRINIT_TASK );
    rc = vdbeIncrPopulate(pIncr);
  }
#endif

  if( rc==SQLITE_OK && (SQLITE_MAX_WORKER_THREADS==0 || eMode!=INCRINIT_TASK) ){
    rc = vdbePmaReaderNext(pReadr);
  }

  return rc;
}