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
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_5__ {int nChild; scalar_t__ bEof; scalar_t__ bNomatch; int /*<<< orphan*/  iRowid; struct TYPE_5__** apChild; } ;
typedef  TYPE_1__ Fts5ExprNode ;
typedef  int /*<<< orphan*/  Fts5Expr ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5ExprNodeNext (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5ExprNodeTest_OR (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ fts5RowidCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5ExprNodeNext_OR(
  Fts5Expr *pExpr, 
  Fts5ExprNode *pNode,
  int bFromValid,
  i64 iFrom
){
  int i;
  i64 iLast = pNode->iRowid;

  for(i=0; i<pNode->nChild; i++){
    Fts5ExprNode *p1 = pNode->apChild[i];
    assert( p1->bEof || fts5RowidCmp(pExpr, p1->iRowid, iLast)>=0 );
    if( p1->bEof==0 ){
      if( (p1->iRowid==iLast) 
       || (bFromValid && fts5RowidCmp(pExpr, p1->iRowid, iFrom)<0)
      ){
        int rc = fts5ExprNodeNext(pExpr, p1, bFromValid, iFrom);
        if( rc!=SQLITE_OK ){
          pNode->bNomatch = 0;
          return rc;
        }
      }
    }
  }

  fts5ExprNodeTest_OR(pExpr, pNode);
  return SQLITE_OK;
}