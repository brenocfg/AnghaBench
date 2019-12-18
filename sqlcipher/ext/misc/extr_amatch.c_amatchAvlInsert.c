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
struct TYPE_7__ {int height; scalar_t__ imbalance; struct TYPE_7__* pAfter; struct TYPE_7__* pBefore; struct TYPE_7__* pUp; int /*<<< orphan*/  zKey; } ;
typedef  TYPE_1__ amatch_avl ;

/* Variables and functions */
 TYPE_1__* amatchAvlBalance (TYPE_1__*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static amatch_avl *amatchAvlInsert(amatch_avl **ppHead, amatch_avl *pNew){
  int c;
  amatch_avl *p = *ppHead;
  if( p==0 ){
    p = pNew;
    pNew->pUp = 0;
  }else{
    while( p ){
      c = strcmp(pNew->zKey, p->zKey);
      if( c<0 ){
        if( p->pBefore ){
          p = p->pBefore;
        }else{
          p->pBefore = pNew;
          pNew->pUp = p;
          break;
        }
      }else if( c>0 ){
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
  *ppHead = amatchAvlBalance(p);
  /* assert( amatchAvlIntegrity(*ppHead) ); */
  /* assert( amatchAvlIntegrity2(*ppHead) ); */
  return 0;
}