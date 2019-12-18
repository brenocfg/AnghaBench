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
typedef  int /*<<< orphan*/  Token ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3ExprAddCollateToken (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3TokenInit (int /*<<< orphan*/ *,char*) ; 

Expr *sqlite3ExprAddCollateString(Parse *pParse, Expr *pExpr, const char *zC){
  Token s;
  assert( zC!=0 );
  sqlite3TokenInit(&s, (char*)zC);
  return sqlite3ExprAddCollateToken(pParse, pExpr, &s, 0);
}