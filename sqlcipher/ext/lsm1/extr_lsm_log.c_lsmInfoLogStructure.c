#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* aRegion; } ;
struct TYPE_8__ {TYPE_4__ log; } ;
struct TYPE_10__ {scalar_t__ pCsr; scalar_t__ nTransOpen; int /*<<< orphan*/  pEnv; TYPE_1__ treehdr; } ;
typedef  TYPE_3__ lsm_db ;
struct TYPE_9__ {scalar_t__ iEnd; scalar_t__ iStart; } ;
typedef  TYPE_4__ DbLog ;

/* Variables and functions */
 int LSM_NOMEM_BKPT ; 
 int LSM_OK ; 
 int logReclaimSpace (TYPE_3__*) ; 
 char* lsmMallocPrintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 int lsmTreeLoadHeader (TYPE_3__*,int /*<<< orphan*/ ) ; 

int lsmInfoLogStructure(lsm_db *pDb, char **pzVal){
  int rc = LSM_OK;
  char *zVal = 0;

  /* If there is no read or write transaction open, read the latest 
  ** tree-header from shared-memory to report on. If necessary, update
  ** it based on the contents of the database header.  
  **
  ** No locks are taken here - these are passive read operations only.
  */
  if( pDb->pCsr==0 && pDb->nTransOpen==0 ){
    rc = lsmTreeLoadHeader(pDb, 0);
    if( rc==LSM_OK ) rc = logReclaimSpace(pDb);
  }

  if( rc==LSM_OK ){
    DbLog *pLog = &pDb->treehdr.log;
    zVal = lsmMallocPrintf(pDb->pEnv, 
        "%d %d %d %d %d %d", 
        (int)pLog->aRegion[0].iStart, (int)pLog->aRegion[0].iEnd,
        (int)pLog->aRegion[1].iStart, (int)pLog->aRegion[1].iEnd,
        (int)pLog->aRegion[2].iStart, (int)pLog->aRegion[2].iEnd
    );
    if( !zVal ) rc = LSM_NOMEM_BKPT;
  }

  *pzVal = zVal;
  return rc;
}