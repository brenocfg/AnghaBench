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
struct TYPE_11__ {int /*<<< orphan*/  pEnv; int /*<<< orphan*/ * pFS; int /*<<< orphan*/ * pWorker; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_13__ {char* z; } ;
struct TYPE_12__ {int iFirst; int iLastPg; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__ Segment ;
typedef  TYPE_3__ LsmString ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  int /*<<< orphan*/  FileSystem ;

/* Variables and functions */
 int LSM_BUSY ; 
 int LSM_ERROR ; 
 int LSM_OK ; 
 TYPE_2__* findSegment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsBlockNext (int /*<<< orphan*/ *,TYPE_2__*,int,int*) ; 
 int fsFirstPageOnBlock (int /*<<< orphan*/ *,int) ; 
 int fsLastPageOnBlock (int /*<<< orphan*/ *,int) ; 
 int fsPageToBlock (int /*<<< orphan*/ *,int) ; 
 int lsmBeginWork (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmFinishWork (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lsmStringAppendf (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  lsmStringInit (TYPE_3__*,int /*<<< orphan*/ ) ; 

int lsmInfoArrayStructure(
  lsm_db *pDb, 
  int bBlock,                     /* True for block numbers only */
  LsmPgno iFirst,
  char **pzOut
){
  int rc = LSM_OK;
  Snapshot *pWorker;              /* Worker snapshot */
  Segment *pArray = 0;            /* Array to report on */
  int bUnlock = 0;

  *pzOut = 0;
  if( iFirst==0 ) return LSM_ERROR;

  /* Obtain the worker snapshot */
  pWorker = pDb->pWorker;
  if( !pWorker ){
    rc = lsmBeginWork(pDb);
    if( rc!=LSM_OK ) return rc;
    pWorker = pDb->pWorker;
    bUnlock = 1;
  }

  /* Search for the array that starts on page iFirst */
  pArray = findSegment(pWorker, iFirst);

  if( pArray==0 ){
    /* Could not find the requested array. This is an error. */
    rc = LSM_ERROR;
  }else{
    FileSystem *pFS = pDb->pFS;
    LsmString str;
    int iBlk;
    int iLastBlk;
   
    iBlk = fsPageToBlock(pFS, pArray->iFirst);
    iLastBlk = fsPageToBlock(pFS, pArray->iLastPg);

    lsmStringInit(&str, pDb->pEnv);
    if( bBlock ){
      lsmStringAppendf(&str, "%d", iBlk);
      while( iBlk!=iLastBlk ){
        fsBlockNext(pFS, pArray, iBlk, &iBlk);
        lsmStringAppendf(&str, " %d", iBlk);
      }
    }else{
      lsmStringAppendf(&str, "%d", pArray->iFirst);
      while( iBlk!=iLastBlk ){
        lsmStringAppendf(&str, " %d", fsLastPageOnBlock(pFS, iBlk));
        fsBlockNext(pFS, pArray, iBlk, &iBlk);
        lsmStringAppendf(&str, " %d", fsFirstPageOnBlock(pFS, iBlk));
      }
      lsmStringAppendf(&str, " %d", pArray->iLastPg);
    }

    *pzOut = str.z;
  }

  if( bUnlock ){
    int rcwork = LSM_BUSY;
    lsmFinishWork(pDb, 0, &rcwork);
  }
  return rc;
}