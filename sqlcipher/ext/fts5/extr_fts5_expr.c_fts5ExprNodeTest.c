#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ bEof; int eType; } ;
typedef  TYPE_1__ Fts5ExprNode ;
typedef  int /*<<< orphan*/  Fts5Expr ;

/* Variables and functions */
#define  FTS5_AND 131 
 int FTS5_NOT ; 
#define  FTS5_OR 130 
#define  FTS5_STRING 129 
#define  FTS5_TERM 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5ExprNodeTest_AND (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int fts5ExprNodeTest_NOT (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fts5ExprNodeTest_OR (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int fts5ExprNodeTest_STRING (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int fts5ExprNodeTest_TERM (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int fts5ExprNodeTest(
  Fts5Expr *pExpr,                /* Expression of which pNode is a part */
  Fts5ExprNode *pNode             /* Expression node to test */
){
  int rc = SQLITE_OK;
  if( pNode->bEof==0 ){
    switch( pNode->eType ){

      case FTS5_STRING: {
        rc = fts5ExprNodeTest_STRING(pExpr, pNode);
        break;
      }

      case FTS5_TERM: {
        rc = fts5ExprNodeTest_TERM(pExpr, pNode);
        break;
      }

      case FTS5_AND: {
        rc = fts5ExprNodeTest_AND(pExpr, pNode);
        break;
      }

      case FTS5_OR: {
        fts5ExprNodeTest_OR(pExpr, pNode);
        break;
      }

      default: assert( pNode->eType==FTS5_NOT ); {
        rc = fts5ExprNodeTest_NOT(pExpr, pNode);
        break;
      }
    }
  }
  return rc;
}