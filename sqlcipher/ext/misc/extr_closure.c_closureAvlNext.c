#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* pAfter; struct TYPE_6__* pUp; } ;
typedef  TYPE_1__ closure_avl ;

/* Variables and functions */
 TYPE_1__* closureAvlFirst (TYPE_1__*) ; 

closure_avl *closureAvlNext(closure_avl *p){
  closure_avl *pPrev = 0;
  while( p && p->pAfter==pPrev ){
    pPrev = p;
    p = p->pUp;
  }
  if( p && pPrev==0 ){
    p = closureAvlFirst(p->pAfter);
  }
  return p;
}