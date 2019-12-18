#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_7__* pWorker; } ;
typedef  TYPE_1__ lsm_db ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_10__ {int nBlock; } ;
struct TYPE_9__ {int nBlock; int /*<<< orphan*/  iInUse; } ;
typedef  TYPE_2__ DbTruncateCtx ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (TYPE_7__*) ; 
 int /*<<< orphan*/  dbTruncateCb ; 
 int freelistAppend (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  lsmLogMessage (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int lsmWalkFreelist (TYPE_1__*,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int dbTruncate(lsm_db *pDb, i64 iInUse){
  int rc = LSM_OK;
#if 0
  int i;
  DbTruncateCtx ctx;

  assert( pDb->pWorker );
  ctx.nBlock = pDb->pWorker->nBlock;
  ctx.iInUse = iInUse;

  rc = lsmWalkFreelist(pDb, 1, dbTruncateCb, (void *)&ctx);
  for(i=ctx.nBlock+1; rc==LSM_OK && i<=pDb->pWorker->nBlock; i++){
    rc = freelistAppend(pDb, i, -1);
  }

  if( rc==LSM_OK ){
#ifdef LSM_LOG_FREELIST
    if( ctx.nBlock!=pDb->pWorker->nBlock ){
      lsmLogMessage(pDb, 0, 
          "dbTruncate(): truncated db to %d blocks",ctx.nBlock
      );
    }
#endif
    pDb->pWorker->nBlock = ctx.nBlock;
  }
#endif
  return rc;
}