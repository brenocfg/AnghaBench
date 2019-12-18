#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_9__ {int (* xSync ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ lsm_env ;
struct TYPE_12__ {int nSector; TYPE_1__* aSector; } ;
struct TYPE_11__ {int bCrashed; scalar_t__ nAutoCrash; int /*<<< orphan*/  pWriteCtx; int /*<<< orphan*/  (* xWriteHook ) (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;scalar_t__ bPrepareCrash; TYPE_5__* aFile; } ;
struct TYPE_10__ {size_t bLog; int /*<<< orphan*/  pReal; TYPE_4__* pDb; } ;
struct TYPE_8__ {scalar_t__ aOld; } ;
typedef  TYPE_3__ LsmFile ;
typedef  TYPE_4__ LsmDb ;
typedef  TYPE_5__ FileData ;

/* Variables and functions */
 int LSM_IOERR ; 
 int /*<<< orphan*/  doSystemCrash (TYPE_4__*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 TYPE_2__* tdb_lsm_env () ; 
 int /*<<< orphan*/  testFree (scalar_t__) ; 

__attribute__((used)) static int testEnvSync(lsm_file *pFile){
  lsm_env *pRealEnv = tdb_lsm_env();
  LsmFile *p = (LsmFile *)pFile;
  LsmDb *pDb = p->pDb;
  FileData *pData = &pDb->aFile[p->bLog];
  int i;

  if( pDb->bCrashed ) return LSM_IOERR;

  if( pDb->nAutoCrash ){
    pDb->nAutoCrash--;
    if( pDb->nAutoCrash==0 ){
      doSystemCrash(pDb);
      pDb->bCrashed = 1;
      return LSM_IOERR;
    }
  }

  if( pDb->bPrepareCrash ){
    for(i=0; i<pData->nSector; i++){
      testFree(pData->aSector[i].aOld);
      pData->aSector[i].aOld = 0;
    }
  }

  if( pDb->xWriteHook ){
    int rc;
    int nUs;
    struct timeval t1;
    struct timeval t2;

    gettimeofday(&t1, 0);
    rc = pRealEnv->xSync(p->pReal);
    gettimeofday(&t2, 0);

    nUs = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
    pDb->xWriteHook(pDb->pWriteCtx, p->bLog, 0, 0, nUs);
    return rc;
  }

  return pRealEnv->xSync(p->pReal);
}