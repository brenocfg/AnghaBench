#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Parse ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ IN_RENAME_OBJECT ; 
 int /*<<< orphan*/  TK_NULL ; 
 int /*<<< orphan*/ * sqlite3ExprAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3ExprIsConstant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3RenameExprUnmap (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Expr *sqlite3WindowOffsetExpr(Parse *pParse, Expr *pExpr){
  if( 0==sqlite3ExprIsConstant(pExpr) ){
    if( IN_RENAME_OBJECT ) sqlite3RenameExprUnmap(pParse, pExpr);
    sqlite3ExprDelete(pParse->db, pExpr);
    pExpr = sqlite3ExprAlloc(pParse->db, TK_NULL, 0, 0);
  }
  return pExpr;
}