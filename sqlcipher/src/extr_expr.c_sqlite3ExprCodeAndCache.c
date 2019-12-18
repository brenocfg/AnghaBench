#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_9__ {scalar_t__ op; } ;
struct TYPE_8__ {int nMem; int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Copy ; 
 scalar_t__ TK_REGISTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exprToRegister (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void sqlite3ExprCodeAndCache(Parse *pParse, Expr *pExpr, int target){
  Vdbe *v = pParse->pVdbe;
  int iMem;

  assert( target>0 );
  assert( pExpr->op!=TK_REGISTER );
  sqlite3ExprCode(pParse, pExpr, target);
  iMem = ++pParse->nMem;
  sqlite3VdbeAddOp2(v, OP_Copy, target, iMem);
  exprToRegister(pExpr, iMem);
}