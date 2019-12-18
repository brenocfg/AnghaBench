#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* pAfter; struct TYPE_11__* pBefore; struct TYPE_11__* pUp; } ;
typedef  TYPE_1__ amatch_avl ;

/* Variables and functions */
 TYPE_1__* amatchAvlBalance (TYPE_1__*) ; 
 TYPE_1__* amatchAvlFirst (TYPE_1__*) ; 
 TYPE_1__** amatchAvlFromPtr (TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void amatchAvlRemove(amatch_avl **ppHead, amatch_avl *pOld){
  amatch_avl **ppParent;
  amatch_avl *pBalance = 0;
  /* assert( amatchAvlSearch(*ppHead, pOld->zKey)==pOld ); */
  ppParent = amatchAvlFromPtr(pOld, ppHead);
  if( pOld->pBefore==0 && pOld->pAfter==0 ){
    *ppParent = 0;
    pBalance = pOld->pUp;
  }else if( pOld->pBefore && pOld->pAfter ){
    amatch_avl *pX, *pY;
    pX = amatchAvlFirst(pOld->pAfter);
    *amatchAvlFromPtr(pX, 0) = pX->pAfter;
    if( pX->pAfter ) pX->pAfter->pUp = pX->pUp;
    pBalance = pX->pUp;
    pX->pAfter = pOld->pAfter;
    if( pX->pAfter ){
      pX->pAfter->pUp = pX;
    }else{
      assert( pBalance==pOld );
      pBalance = pX;
    }
    pX->pBefore = pY = pOld->pBefore;
    if( pY ) pY->pUp = pX;
    pX->pUp = pOld->pUp;
    *ppParent = pX;
  }else if( pOld->pBefore==0 ){
    *ppParent = pBalance = pOld->pAfter;
    pBalance->pUp = pOld->pUp;
  }else if( pOld->pAfter==0 ){
    *ppParent = pBalance = pOld->pBefore;
    pBalance->pUp = pOld->pUp;
  }
  *ppHead = amatchAvlBalance(pBalance);
  pOld->pUp = 0;
  pOld->pBefore = 0;
  pOld->pAfter = 0;
  /* assert( amatchAvlIntegrity(*ppHead) ); */
  /* assert( amatchAvlIntegrity2(*ppHead) ); */
}