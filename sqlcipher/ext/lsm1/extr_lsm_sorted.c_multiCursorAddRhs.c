#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* pLevel; int /*<<< orphan*/ * pSeg; } ;
struct TYPE_9__ {int nRight; int /*<<< orphan*/ * aRhs; } ;
struct TYPE_8__ {int nPtr; TYPE_6__* aPtr; TYPE_1__* pDb; } ;
struct TYPE_7__ {int /*<<< orphan*/  pEnv; } ;
typedef  int /*<<< orphan*/  SegmentPtr ;
typedef  TYPE_2__ MultiCursor ;
typedef  TYPE_3__ Level ;

/* Variables and functions */
 int LSM_NOMEM_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__* lsmMallocZero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int multiCursorAddRhs(MultiCursor *pCsr, Level *pLvl){
  int i;
  int nRhs = pLvl->nRight;

  assert( pLvl->nRight>0 );
  assert( pCsr->aPtr==0 );
  pCsr->aPtr = lsmMallocZero(pCsr->pDb->pEnv, sizeof(SegmentPtr) * nRhs);
  if( !pCsr->aPtr ) return LSM_NOMEM_BKPT;
  pCsr->nPtr = nRhs;

  for(i=0; i<nRhs; i++){
    pCsr->aPtr[i].pSeg = &pLvl->aRhs[i];
    pCsr->aPtr[i].pLevel = pLvl;
  }

  return LSM_OK;
}