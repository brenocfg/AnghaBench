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
struct TYPE_5__ {int nChild; scalar_t__ bNomatch; int /*<<< orphan*/  bEof; int /*<<< orphan*/  iRowid; struct TYPE_5__** apChild; } ;
typedef  TYPE_1__ Fts5ExprNode ;
typedef  int /*<<< orphan*/  Fts5Expr ;

/* Variables and functions */
 int fts5NodeCompare (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void fts5ExprNodeTest_OR(
  Fts5Expr *pExpr,                /* Expression of which pNode is a part */
  Fts5ExprNode *pNode             /* Expression node to test */
){
  Fts5ExprNode *pNext = pNode->apChild[0];
  int i;

  for(i=1; i<pNode->nChild; i++){
    Fts5ExprNode *pChild = pNode->apChild[i];
    int cmp = fts5NodeCompare(pExpr, pNext, pChild);
    if( cmp>0 || (cmp==0 && pChild->bNomatch==0) ){
      pNext = pChild;
    }
  }
  pNode->iRowid = pNext->iRowid;
  pNode->bEof = pNext->bEof;
  pNode->bNomatch = pNext->bNomatch;
}