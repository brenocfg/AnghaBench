#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
typedef  TYPE_1__ EditDist3Cost ;

/* Variables and functions */
 scalar_t__ editDist3CostCompare (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static EditDist3Cost *editDist3CostMerge(
  EditDist3Cost *pA,
  EditDist3Cost *pB
){
  EditDist3Cost *pHead = 0;
  EditDist3Cost **ppTail = &pHead;
  EditDist3Cost *p;
  while( pA && pB ){
    if( editDist3CostCompare(pA,pB)<=0 ){
      p = pA;
      pA = pA->pNext;
    }else{
      p = pB;
      pB = pB->pNext;
    }
    *ppTail = p;
    ppTail =  &p->pNext;
  }
  if( pA ){
    *ppTail = pA;
  }else{
    *ppTail = pB;
  }
  return pHead;
}