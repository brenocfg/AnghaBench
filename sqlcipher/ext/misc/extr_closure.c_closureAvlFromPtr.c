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
struct TYPE_5__ {struct TYPE_5__* pBefore; struct TYPE_5__* pAfter; struct TYPE_5__* pUp; } ;
typedef  TYPE_1__ closure_avl ;

/* Variables and functions */

__attribute__((used)) static closure_avl **closureAvlFromPtr(closure_avl *p, closure_avl **pp){
  closure_avl *pUp = p->pUp;
  if( pUp==0 ) return pp;
  if( pUp->pAfter==p ) return &pUp->pAfter;
  return &pUp->pBefore;
}