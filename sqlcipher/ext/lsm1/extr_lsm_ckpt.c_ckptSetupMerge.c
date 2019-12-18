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
typedef  scalar_t__ u32 ;
struct TYPE_9__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_12__ {TYPE_4__* pMerge; } ;
struct TYPE_8__ {int iCell; void* iPg; } ;
struct TYPE_11__ {int nInput; int iOutputOff; int nSkip; void* iCurrentPtr; TYPE_1__ splitkey; TYPE_3__* aInput; } ;
struct TYPE_10__ {int iCell; void* iPg; } ;
typedef  TYPE_3__ MergeInput ;
typedef  TYPE_4__ Merge ;
typedef  TYPE_5__ Level ;

/* Variables and functions */
 int LSM_NOMEM_BKPT ; 
 int LSM_OK ; 
 void* ckptGobble64 (scalar_t__*,int*) ; 
 scalar_t__ lsmMallocZero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ckptSetupMerge(lsm_db *pDb, u32 *aInt, int *piIn, Level *pLevel){
  Merge *pMerge;                  /* Allocated Merge object */
  int nInput;                     /* Number of input segments in merge */
  int iIn = *piIn;                /* Next value to read from aInt[] */
  int i;                          /* Iterator variable */
  int nByte;                      /* Number of bytes to allocate */

  /* Allocate the Merge object. If malloc() fails, return LSM_NOMEM. */
  nInput = (int)aInt[iIn++];
  nByte = sizeof(Merge) + sizeof(MergeInput) * nInput;
  pMerge = (Merge *)lsmMallocZero(pDb->pEnv, nByte);
  if( !pMerge ) return LSM_NOMEM_BKPT;
  pLevel->pMerge = pMerge;

  /* Populate the Merge object. */
  pMerge->aInput = (MergeInput *)&pMerge[1];
  pMerge->nInput = nInput;
  pMerge->iOutputOff = -1;
  pMerge->nSkip = (int)aInt[iIn++];
  for(i=0; i<nInput; i++){
    pMerge->aInput[i].iPg = ckptGobble64(aInt, &iIn);
    pMerge->aInput[i].iCell = (int)aInt[iIn++];
  }
  pMerge->splitkey.iPg = ckptGobble64(aInt, &iIn);
  pMerge->splitkey.iCell = (int)aInt[iIn++];
  pMerge->iCurrentPtr = ckptGobble64(aInt, &iIn);

  /* Set *piIn and return LSM_OK. */
  *piIn = iIn;
  return LSM_OK;
}