#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ rCostX; scalar_t__ pNext; } ;
typedef  TYPE_1__ fuzzer_stem ;
struct TYPE_12__ {int mxQueue; TYPE_1__** aQueue; TYPE_1__* pStem; } ;
typedef  TYPE_2__ fuzzer_cursor ;

/* Variables and functions */
 int FUZZER_NQUEUE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* fuzzerLowestCostStem (TYPE_2__*) ; 
 TYPE_1__* fuzzerMergeStems (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static fuzzer_stem *fuzzerInsert(fuzzer_cursor *pCur, fuzzer_stem *pNew){
  fuzzer_stem *pX;
  int i;

  /* If pCur->pStem exists and is greater than pNew, then make pNew
  ** the new pCur->pStem and insert the old pCur->pStem instead.
  */
  if( (pX = pCur->pStem)!=0 && pX->rCostX>pNew->rCostX ){
    pNew->pNext = 0;
    pCur->pStem = pNew;
    pNew = pX;
  }

  /* Insert the new value */
  pNew->pNext = 0;
  pX = pNew;
  for(i=0; i<=pCur->mxQueue; i++){
    if( pCur->aQueue[i] ){
      pX = fuzzerMergeStems(pX, pCur->aQueue[i]);
      pCur->aQueue[i] = 0;
    }else{
      pCur->aQueue[i] = pX;
      break;
    }
  }
  if( i>pCur->mxQueue ){
    if( i<FUZZER_NQUEUE ){
      pCur->mxQueue = i;
      pCur->aQueue[i] = pX;
    }else{
      assert( pCur->mxQueue==FUZZER_NQUEUE-1 );
      pX = fuzzerMergeStems(pX, pCur->aQueue[FUZZER_NQUEUE-1]);
      pCur->aQueue[FUZZER_NQUEUE-1] = pX;
    }
  }

  return fuzzerLowestCostStem(pCur);
}