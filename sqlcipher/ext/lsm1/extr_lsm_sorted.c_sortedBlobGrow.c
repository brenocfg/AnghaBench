#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_3__ {scalar_t__ pData; int nAlloc; int /*<<< orphan*/ * pEnv; } ;
typedef  TYPE_1__ LsmBlob ;

/* Variables and functions */
 int LSM_NOMEM_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ lsmReallocOrFree (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int sortedBlobGrow(lsm_env *pEnv, LsmBlob *pBlob, int nData){
  assert( pBlob->pEnv==pEnv || (pBlob->pEnv==0 && pBlob->pData==0) );
  if( pBlob->nAlloc<nData ){
    pBlob->pData = lsmReallocOrFree(pEnv, pBlob->pData, nData);
    if( !pBlob->pData ) return LSM_NOMEM_BKPT;
    pBlob->nAlloc = nData;
    pBlob->pEnv = pEnv;
  }
  return LSM_OK;
}