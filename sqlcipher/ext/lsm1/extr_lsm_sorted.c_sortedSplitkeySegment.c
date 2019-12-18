#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nRight; int /*<<< orphan*/ * aRhs; TYPE_2__* pNext; TYPE_4__* pMerge; } ;
struct TYPE_9__ {scalar_t__ iPg; } ;
struct TYPE_10__ {int nInput; TYPE_1__* aInput; TYPE_3__ splitkey; } ;
struct TYPE_8__ {int /*<<< orphan*/  lhs; } ;
struct TYPE_7__ {scalar_t__ iPg; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  TYPE_3__ MergeInput ;
typedef  TYPE_4__ Merge ;
typedef  TYPE_5__ Level ;

/* Variables and functions */

__attribute__((used)) static Segment *sortedSplitkeySegment(Level *pLevel){
  Merge *pMerge = pLevel->pMerge;
  MergeInput *p = &pMerge->splitkey;
  Segment *pSeg;
  int i;

  for(i=0; i<pMerge->nInput; i++){
    if( p->iPg==pMerge->aInput[i].iPg ) break;
  }
  if( pMerge->nInput==(pLevel->nRight+1) && i>=(pMerge->nInput-1) ){
    pSeg = &pLevel->pNext->lhs;
  }else{
    pSeg = &pLevel->aRhs[i];
  }

  return pSeg;
}