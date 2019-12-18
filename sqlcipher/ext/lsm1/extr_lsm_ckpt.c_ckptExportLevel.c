#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_9__ {int flags; scalar_t__ nRight; int /*<<< orphan*/ * aRhs; int /*<<< orphan*/  lhs; scalar_t__ iAge; TYPE_3__* pMerge; } ;
struct TYPE_7__ {scalar_t__ iCell; int /*<<< orphan*/  iPg; } ;
struct TYPE_8__ {int nInput; scalar_t__ nSkip; int /*<<< orphan*/  iCurrentPtr; TYPE_2__ splitkey; TYPE_1__* aInput; } ;
struct TYPE_6__ {scalar_t__ iCell; int /*<<< orphan*/  iPg; } ;
typedef  TYPE_3__ Merge ;
typedef  TYPE_4__ Level ;
typedef  int /*<<< orphan*/  CkptBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ckptAppend64 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ckptExportSegment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  ckptSetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static void ckptExportLevel(
  Level *pLevel,                  /* Level object to serialize */
  CkptBuffer *p,                  /* Append new level record to this ckpt */
  int *piOut,                     /* IN/OUT: Size of checkpoint so far */
  int *pRc                        /* IN/OUT: Error code */
){
  int iOut = *piOut;
  Merge *pMerge;

  pMerge = pLevel->pMerge;
  ckptSetValue(p, iOut++, (u32)pLevel->iAge + (u32)(pLevel->flags<<16), pRc);
  ckptSetValue(p, iOut++, pLevel->nRight, pRc);
  ckptExportSegment(&pLevel->lhs, p, &iOut, pRc);

  assert( (pLevel->nRight>0)==(pMerge!=0) );
  if( pMerge ){
    int i;
    for(i=0; i<pLevel->nRight; i++){
      ckptExportSegment(&pLevel->aRhs[i], p, &iOut, pRc);
    }
    assert( pMerge->nInput==pLevel->nRight 
         || pMerge->nInput==pLevel->nRight+1 
    );
    ckptSetValue(p, iOut++, pMerge->nInput, pRc);
    ckptSetValue(p, iOut++, pMerge->nSkip, pRc);
    for(i=0; i<pMerge->nInput; i++){
      ckptAppend64(p, &iOut, pMerge->aInput[i].iPg, pRc);
      ckptSetValue(p, iOut++, pMerge->aInput[i].iCell, pRc);
    }
    ckptAppend64(p, &iOut, pMerge->splitkey.iPg, pRc);
    ckptSetValue(p, iOut++, pMerge->splitkey.iCell, pRc);
    ckptAppend64(p, &iOut, pMerge->iCurrentPtr, pRc);
  }

  *piOut = iOut;
}