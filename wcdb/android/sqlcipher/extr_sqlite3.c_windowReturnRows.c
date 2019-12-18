#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  iEphCsr; } ;
typedef  TYPE_1__ Window ;
typedef  int /*<<< orphan*/  Vdbe ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_IfPos ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 scalar_t__ sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  windowAggFinal (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowAggStep (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  windowReturnOneRow (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 

__attribute__((used)) static void windowReturnRows(
  Parse *pParse,
  Window *pMWin,                  /* List of window functions */
  int regCtr,                     /* Register containing number of rows */
  int regGosub,                   /* Register for Gosub addrGosub */
  int addrGosub,                  /* Address of sub-routine for ReturnOneRow */
  int regInvArg,                  /* Array of registers for xInverse args */
  int regInvSize                  /* Register containing size of partition */
){
  int addr;
  Vdbe *v = sqlite3GetVdbe(pParse);
  windowAggFinal(pParse, pMWin, 0);
  addr = sqlite3VdbeAddOp3(v, OP_IfPos, regCtr, sqlite3VdbeCurrentAddr(v)+2 ,1);
  VdbeCoverage(v);
  sqlite3VdbeAddOp2(v, OP_Goto, 0, 0);
  windowReturnOneRow(pParse, pMWin, regGosub, addrGosub);
  if( regInvArg ){
    windowAggStep(pParse, pMWin, pMWin->iEphCsr, 1, regInvArg, regInvSize);
  }
  sqlite3VdbeAddOp2(v, OP_Next, pMWin->iEphCsr, addr);
  VdbeCoverage(v);
  sqlite3VdbeJumpHere(v, addr+1);   /* The OP_Goto */
}