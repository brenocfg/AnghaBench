#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_7__ {scalar_t__ nMapLimit; int nMetaRwSize; int /*<<< orphan*/  pEnv; int /*<<< orphan*/  fdDb; int /*<<< orphan*/  nMetasize; } ;
struct TYPE_6__ {int iPg; struct TYPE_6__* aData; scalar_t__ bWrite; TYPE_2__* pFS; } ;
typedef  TYPE_1__ MetaPage ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int lsmEnvWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,TYPE_1__*) ; 

int lsmFsMetaPageRelease(MetaPage *pPg){
  int rc = LSM_OK;
  if( pPg ){
    FileSystem *pFS = pPg->pFS;

    if( pFS->nMapLimit==0 ){
      if( pPg->bWrite ){
        i64 iOff = (pPg->iPg==2 ? pFS->nMetasize : 0);
        int nWrite = pFS->nMetaRwSize;
        rc = lsmEnvWrite(pFS->pEnv, pFS->fdDb, iOff, pPg->aData, nWrite);
      }
      lsmFree(pFS->pEnv, pPg->aData);
    }

    lsmFree(pFS->pEnv, pPg);
  }
  return rc;
}