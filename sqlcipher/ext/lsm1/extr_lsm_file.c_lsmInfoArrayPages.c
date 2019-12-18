#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pEnv; int /*<<< orphan*/ * pFS; int /*<<< orphan*/ * pWorker; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_9__ {char* z; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__ LsmString ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  int /*<<< orphan*/  FileSystem ;

/* Variables and functions */
 int LSM_BUSY ; 
 int LSM_ERROR ; 
 int LSM_OK ; 
 int /*<<< orphan*/ * findSegment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lsmBeginWork (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmFinishWork (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,char*) ; 
 int lsmFsDbPageGet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int lsmFsDbPageNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsPageNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmStringAppendf (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmStringInit (TYPE_2__*,int /*<<< orphan*/ ) ; 

int lsmInfoArrayPages(lsm_db *pDb, LsmPgno iFirst, char **pzOut){
  int rc = LSM_OK;
  Snapshot *pWorker;              /* Worker snapshot */
  Segment *pSeg = 0;              /* Array to report on */
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
  pSeg = findSegment(pWorker, iFirst);

  if( pSeg==0 ){
    /* Could not find the requested array. This is an error. */
    rc = LSM_ERROR;
  }else{
    Page *pPg = 0;
    FileSystem *pFS = pDb->pFS;
    LsmString str;

    lsmStringInit(&str, pDb->pEnv);
    rc = lsmFsDbPageGet(pFS, pSeg, iFirst, &pPg);
    while( rc==LSM_OK && pPg ){
      Page *pNext = 0;
      lsmStringAppendf(&str, " %lld", lsmFsPageNumber(pPg));
      rc = lsmFsDbPageNext(pSeg, pPg, 1, &pNext);
      lsmFsPageRelease(pPg);
      pPg = pNext;
    }

    if( rc!=LSM_OK ){
      lsmFree(pDb->pEnv, str.z);
    }else{
      *pzOut = str.z;
    }
  }

  if( bUnlock ){
    int rcwork = LSM_BUSY;
    lsmFinishWork(pDb, 0, &rcwork);
  }
  return rc;
}