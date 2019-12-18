#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nRight; scalar_t__ pSplitKey; int /*<<< orphan*/ * aRhs; int /*<<< orphan*/  lhs; } ;
struct TYPE_8__ {int nPtr; int /*<<< orphan*/  pDb; TYPE_1__* aPtr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pSeg; TYPE_3__* pLevel; } ;
typedef  TYPE_2__ MultiCursor ;
typedef  TYPE_3__ Level ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  sortedSplitkey (int /*<<< orphan*/ ,TYPE_3__*,int*) ; 

__attribute__((used)) static void multiCursorAddOne(MultiCursor *pCsr, Level *pLvl, int *pRc){
  if( *pRc==LSM_OK ){
    int iPtr = pCsr->nPtr;
    int i;
    pCsr->aPtr[iPtr].pLevel = pLvl;
    pCsr->aPtr[iPtr].pSeg = &pLvl->lhs;
    iPtr++;
    for(i=0; i<pLvl->nRight; i++){
      pCsr->aPtr[iPtr].pLevel = pLvl;
      pCsr->aPtr[iPtr].pSeg = &pLvl->aRhs[i];
      iPtr++;
    }

    if( pLvl->nRight && pLvl->pSplitKey==0 ){
      sortedSplitkey(pCsr->pDb, pLvl, pRc);
    }
    pCsr->nPtr = iPtr;
  }
}