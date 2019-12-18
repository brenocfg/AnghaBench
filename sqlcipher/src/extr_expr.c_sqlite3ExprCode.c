#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ op; int iTable; } ;
struct TYPE_9__ {int nMem; scalar_t__ pVdbe; TYPE_1__* db; } ;
struct TYPE_8__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_SCopy ; 
 scalar_t__ TK_REGISTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3ExprCodeTarget (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (scalar_t__,int /*<<< orphan*/ ,int,int) ; 

void sqlite3ExprCode(Parse *pParse, Expr *pExpr, int target){
  int inReg;

  assert( target>0 && target<=pParse->nMem );
  if( pExpr && pExpr->op==TK_REGISTER ){
    sqlite3VdbeAddOp2(pParse->pVdbe, OP_Copy, pExpr->iTable, target);
  }else{
    inReg = sqlite3ExprCodeTarget(pParse, pExpr, target);
    assert( pParse->pVdbe!=0 || pParse->db->mallocFailed );
    if( inReg!=target && pParse->pVdbe ){
      sqlite3VdbeAddOp2(pParse->pVdbe, OP_SCopy, inReg, target);
    }
  }
}