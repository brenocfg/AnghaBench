#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* pUp; struct TYPE_5__* pBefore; struct TYPE_5__* pAfter; } ;
typedef  TYPE_1__ closure_avl ;

/* Variables and functions */
 int /*<<< orphan*/  closureAvlRecomputeHeight (TYPE_1__*) ; 

__attribute__((used)) static closure_avl *closureAvlRotateBefore(closure_avl *pP){
  closure_avl *pB = pP->pBefore;
  closure_avl *pY = pB->pAfter;
  pB->pUp = pP->pUp;
  pB->pAfter = pP;
  pP->pUp = pB;
  pP->pBefore = pY;
  if( pY ) pY->pUp = pP;
  closureAvlRecomputeHeight(pP);
  closureAvlRecomputeHeight(pB);
  return pB;
}