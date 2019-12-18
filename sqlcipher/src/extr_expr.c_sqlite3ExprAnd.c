#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TK_AND ; 
 int /*<<< orphan*/  TK_INTEGER ; 
 scalar_t__ exprAlwaysFalse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3ExprAlloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprAttachSubtrees (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3IntTokens ; 

Expr *sqlite3ExprAnd(sqlite3 *db, Expr *pLeft, Expr *pRight){
  if( pLeft==0 ){
    return pRight;
  }else if( pRight==0 ){
    return pLeft;
  }else if( exprAlwaysFalse(pLeft) || exprAlwaysFalse(pRight) ){
    sqlite3ExprDelete(db, pLeft);
    sqlite3ExprDelete(db, pRight);
    return sqlite3ExprAlloc(db, TK_INTEGER, &sqlite3IntTokens[0], 0);
  }else{
    Expr *pNew = sqlite3ExprAlloc(db, TK_AND, 0, 0);
    sqlite3ExprAttachSubtrees(db, pNew, pLeft, pRight);
    return pNew;
  }
}