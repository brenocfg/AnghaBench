#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int op; int iAgg; int /*<<< orphan*/  nHeight; } ;
struct TYPE_16__ {scalar_t__ nErr; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  IN_RENAME_OBJECT ; 
 int TK_AND ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* sqlite3DbMallocRawNN (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* sqlite3ExprAnd (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ExprAttachSubtrees (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ExprCheckHeight (TYPE_1__*,int /*<<< orphan*/ ) ; 

Expr *sqlite3PExpr(
  Parse *pParse,          /* Parsing context */
  int op,                 /* Expression opcode */
  Expr *pLeft,            /* Left operand */
  Expr *pRight            /* Right operand */
){
  Expr *p;
  if( op==TK_AND && pParse->nErr==0 && !IN_RENAME_OBJECT ){
    /* Take advantage of short-circuit false optimization for AND */
    p = sqlite3ExprAnd(pParse->db, pLeft, pRight);
  }else{
    p = sqlite3DbMallocRawNN(pParse->db, sizeof(Expr));
    if( p ){
      memset(p, 0, sizeof(Expr));
      p->op = op & 0xff;
      p->iAgg = -1;
    }
    sqlite3ExprAttachSubtrees(pParse->db, p, pLeft, pRight);
  }
  if( p ) {
    sqlite3ExprCheckHeight(pParse, p->nHeight);
  }
  return p;
}