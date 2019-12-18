#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  iUsedShmid; } ;
struct TYPE_14__ {scalar_t__ bReadonly; int iRwclient; TYPE_4__* pShmhdr; TYPE_2__ treehdr; scalar_t__* apShm; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_3__ lsm_db ;
struct TYPE_15__ {TYPE_1__* aReader; int /*<<< orphan*/  aSnap1; } ;
struct TYPE_12__ {int /*<<< orphan*/  iTreeId; int /*<<< orphan*/  iLsmId; } ;
typedef  TYPE_4__ ShmHeader ;

/* Variables and functions */
 int LSM_BUSY ; 
 scalar_t__ LSM_LOCK_DMS1 ; 
 scalar_t__ LSM_LOCK_DMS2 ; 
 scalar_t__ LSM_LOCK_DMS3 ; 
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int LSM_LOCK_NRWCLIENT ; 
 scalar_t__ LSM_LOCK_RWCLIENT (int) ; 
 int /*<<< orphan*/  LSM_LOCK_SHARED ; 
 int /*<<< orphan*/  LSM_LOCK_UNLOCK ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmCheckpointId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lsmCheckpointRecover (TYPE_3__*) ; 
 int /*<<< orphan*/  lsmEnvSleep (int /*<<< orphan*/ ,int) ; 
 int lsmLogRecover (TYPE_3__*) ; 
 int lsmShmCacheChunks (TYPE_3__*,int) ; 
 int lsmShmLock (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int lsmShmTestLock (TYPE_3__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int doDbConnect(lsm_db *pDb){
  const int nUsMax = 100000;      /* Max value for nUs */
  int nUs = 1000;                 /* us to wait between DMS1 attempts */
  int rc;

  /* Obtain a pointer to the shared-memory header */
  assert( pDb->pShmhdr==0 );
  assert( pDb->bReadonly==0 );

  /* Block for an exclusive lock on DMS1. This lock serializes all calls
  ** to doDbConnect() and doDbDisconnect() across all processes.  */
  while( 1 ){
    rc = lsmShmLock(pDb, LSM_LOCK_DMS1, LSM_LOCK_EXCL, 1);
    if( rc!=LSM_BUSY ) break;
    lsmEnvSleep(pDb->pEnv, nUs);
    nUs = nUs * 2;
    if( nUs>nUsMax ) nUs = nUsMax;
  }
  if( rc==LSM_OK ){
    rc = lsmShmCacheChunks(pDb, 1);
  }
  if( rc!=LSM_OK ) return rc;
  pDb->pShmhdr = (ShmHeader *)pDb->apShm[0];

  /* Try an exclusive lock on DMS2/DMS3. If successful, this is the first 
  ** and only connection to the database. In this case initialize the 
  ** shared-memory and run log file recovery.  */
  assert( LSM_LOCK_DMS3==1+LSM_LOCK_DMS2 );
  rc = lsmShmTestLock(pDb, LSM_LOCK_DMS2, 2, LSM_LOCK_EXCL);
  if( rc==LSM_OK ){
    memset(pDb->pShmhdr, 0, sizeof(ShmHeader));
    rc = lsmCheckpointRecover(pDb);
    if( rc==LSM_OK ){
      rc = lsmLogRecover(pDb);
    }
    if( rc==LSM_OK ){
      ShmHeader *pShm = pDb->pShmhdr;
      pShm->aReader[0].iLsmId = lsmCheckpointId(pShm->aSnap1, 0);
      pShm->aReader[0].iTreeId = pDb->treehdr.iUsedShmid;
    }
  }else if( rc==LSM_BUSY ){
    rc = LSM_OK;
  }

  /* Take a shared lock on DMS2. In multi-process mode this lock "cannot" 
  ** fail, as connections may only hold an exclusive lock on DMS2 if they 
  ** first hold an exclusive lock on DMS1. And this connection is currently 
  ** holding the exclusive lock on DSM1. 
  **
  ** However, if some other connection has the database open in single-process
  ** mode, this operation will fail. In this case, return the error to the
  ** caller - the attempt to connect to the db has failed.
  */
  if( rc==LSM_OK ){
    rc = lsmShmLock(pDb, LSM_LOCK_DMS2, LSM_LOCK_SHARED, 0);
  }

  /* If anything went wrong, unlock DMS2. Otherwise, try to take an exclusive
  ** lock on one of the LSM_LOCK_RWCLIENT() locks. Unlock DMS1 in any case. */
  if( rc!=LSM_OK ){
    pDb->pShmhdr = 0;
  }else{
    int i;
    for(i=0; i<LSM_LOCK_NRWCLIENT; i++){
      int rc2 = lsmShmLock(pDb, LSM_LOCK_RWCLIENT(i), LSM_LOCK_EXCL, 0);
      if( rc2==LSM_OK ) pDb->iRwclient = i;
      if( rc2!=LSM_BUSY ){
        rc = rc2;
        break;
      }
    }
  }
  lsmShmLock(pDb, LSM_LOCK_DMS1, LSM_LOCK_UNLOCK, 0);

  return rc;
}