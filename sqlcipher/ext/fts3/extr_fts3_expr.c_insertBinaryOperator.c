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
struct TYPE_6__ {struct TYPE_6__* pParent; struct TYPE_6__* pLeft; struct TYPE_6__* pRight; } ;
typedef  TYPE_1__ Fts3Expr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ opPrecedence (TYPE_1__*) ; 

__attribute__((used)) static void insertBinaryOperator(
  Fts3Expr **ppHead,       /* Pointer to the root node of a tree */
  Fts3Expr *pPrev,         /* Node most recently inserted into the tree */
  Fts3Expr *pNew           /* New binary node to insert into expression tree */
){
  Fts3Expr *pSplit = pPrev;
  while( pSplit->pParent && opPrecedence(pSplit->pParent)<=opPrecedence(pNew) ){
    pSplit = pSplit->pParent;
  }

  if( pSplit->pParent ){
    assert( pSplit->pParent->pRight==pSplit );
    pSplit->pParent->pRight = pNew;
    pNew->pParent = pSplit->pParent;
  }else{
    *ppHead = pNew;
  }
  pNew->pLeft = pSplit;
  pSplit->pParent = pNew;
}