#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ pWorker; scalar_t__ nTransOpen; scalar_t__ pClient; int /*<<< orphan*/  aSnapshot; int /*<<< orphan*/  pEnv; scalar_t__ pCsr; int /*<<< orphan*/  nMerge; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_14__ {struct TYPE_14__* pNext; } ;
typedef  TYPE_2__ Level ;

/* Variables and functions */
 int LSM_BUSY ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int doLsmWork (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int lsmCheckpointDeserialize (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int lsmCheckpointLoad (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* lsmDbSnapshotLevel (scalar_t__) ; 
 int /*<<< orphan*/  lsmFreeSnapshot (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lsmLogMessage (TYPE_1__*,int,char*,int,int,int) ; 
 int /*<<< orphan*/  lsmMCursorFreeCache (TYPE_1__*) ; 
 int lsmRestoreCursors (TYPE_1__*) ; 
 int lsmSaveCursors (TYPE_1__*) ; 
 scalar_t__ lsmTreeHasOld (TYPE_1__*) ; 

int lsmSortedAutoWork(
  lsm_db *pDb,                    /* Database handle */
  int nUnit                       /* Pages of data written to in-memory tree */
){
  int rc = LSM_OK;                /* Return code */
  int nDepth = 0;                 /* Current height of tree (longest path) */
  Level *pLevel;                  /* Used to iterate through levels */
  int bRestore = 0;

  assert( pDb->pWorker==0 );
  assert( pDb->nTransOpen>0 );

  /* Determine how many units of work to do before returning. One unit of
  ** work is achieved by writing one page (~4KB) of merged data.  */
  for(pLevel=lsmDbSnapshotLevel(pDb->pClient); pLevel; pLevel=pLevel->pNext){
    /* nDepth += LSM_MAX(1, pLevel->nRight); */
    nDepth += 1;
  }
  if( lsmTreeHasOld(pDb) ){
    nDepth += 1;
    bRestore = 1;
    rc = lsmSaveCursors(pDb);
    if( rc!=LSM_OK ) return rc;
  }

  if( nDepth>0 ){
    int nRemaining;               /* Units of work to do before returning */

    nRemaining = nUnit * nDepth;
#ifdef LSM_LOG_WORK
    lsmLogMessage(pDb, rc, "lsmSortedAutoWork(): %d*%d = %d pages", 
        nUnit, nDepth, nRemaining);
#endif
    assert( nRemaining>=0 );
    rc = doLsmWork(pDb, pDb->nMerge, nRemaining, 0);
    if( rc==LSM_BUSY ) rc = LSM_OK;

    if( bRestore && pDb->pCsr ){
      lsmMCursorFreeCache(pDb);
      lsmFreeSnapshot(pDb->pEnv, pDb->pClient);
      pDb->pClient = 0;
      if( rc==LSM_OK ){
        rc = lsmCheckpointLoad(pDb, 0);
      }
      if( rc==LSM_OK ){
        rc = lsmCheckpointDeserialize(pDb, 0, pDb->aSnapshot, &pDb->pClient);
      }
      if( rc==LSM_OK ){
        rc = lsmRestoreCursors(pDb);
      }
    }
  }

  return rc;
}