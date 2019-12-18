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
struct TYPE_7__ {scalar_t__ id; int height; scalar_t__ imbalance; struct TYPE_7__* pAfter; struct TYPE_7__* pBefore; struct TYPE_7__* pUp; } ;
typedef  TYPE_1__ closure_avl ;

/* Variables and functions */
 TYPE_1__* closureAvlBalance (TYPE_1__*) ; 

__attribute__((used)) static closure_avl *closureAvlInsert(
  closure_avl **ppHead,  /* Head of the tree */
  closure_avl *pNew      /* New node to be inserted */
){
  closure_avl *p = *ppHead;
  if( p==0 ){
    p = pNew;
    pNew->pUp = 0;
  }else{
    while( p ){
      if( pNew->id<p->id ){
        if( p->pBefore ){
          p = p->pBefore;
        }else{
          p->pBefore = pNew;
          pNew->pUp = p;
          break;
        }
      }else if( pNew->id>p->id ){
        if( p->pAfter ){
          p = p->pAfter;
        }else{
          p->pAfter = pNew;
          pNew->pUp = p;
          break;
        }
      }else{
        return p;
      }
    }
  }
  pNew->pBefore = 0;
  pNew->pAfter = 0;
  pNew->height = 1;
  pNew->imbalance = 0;
  *ppHead = closureAvlBalance(p);
  return 0;
}