#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_10__ {int bEof; scalar_t__ bNomatch; TYPE_3__* pNear; } ;
struct TYPE_9__ {TYPE_2__** apPhrase; } ;
struct TYPE_8__ {TYPE_1__* aTerm; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pIter; } ;
typedef  int /*<<< orphan*/  Fts5IndexIter ;
typedef  TYPE_4__ Fts5ExprNode ;
typedef  int /*<<< orphan*/  Fts5Expr ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5ExprNodeTest_TERM (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ sqlite3Fts5IterEof (int /*<<< orphan*/ *) ; 
 int sqlite3Fts5IterNext (int /*<<< orphan*/ *) ; 
 int sqlite3Fts5IterNextFrom (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5ExprNodeNext_TERM(
  Fts5Expr *pExpr, 
  Fts5ExprNode *pNode,
  int bFromValid,
  i64 iFrom
){
  int rc;
  Fts5IndexIter *pIter = pNode->pNear->apPhrase[0]->aTerm[0].pIter;

  assert( pNode->bEof==0 );
  if( bFromValid ){
    rc = sqlite3Fts5IterNextFrom(pIter, iFrom);
  }else{
    rc = sqlite3Fts5IterNext(pIter);
  }
  if( rc==SQLITE_OK && sqlite3Fts5IterEof(pIter)==0 ){
    rc = fts5ExprNodeTest_TERM(pExpr, pNode);
  }else{
    pNode->bEof = 1;
    pNode->bNomatch = 0;
  }
  return rc;
}