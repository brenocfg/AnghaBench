#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int csrApp; int regResult; int iEphCsr; int iArgCol; int regApp; TYPE_3__* pOwner; TYPE_5__* pFunc; struct TYPE_10__* pNextWin; } ;
typedef  TYPE_4__ Window ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_11__ {scalar_t__ zName; } ;
struct TYPE_8__ {TYPE_1__* pList; } ;
struct TYPE_9__ {TYPE_2__ x; } ;
struct TYPE_7__ {int nExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_5__ FuncDef ;

/* Variables and functions */
 int OP_Add ; 
 int /*<<< orphan*/  OP_AddImm ; 
 int OP_Column ; 
 int /*<<< orphan*/  OP_Gosub ; 
 int OP_Gt ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_Rowid ; 
 int OP_SeekRowid ; 
 int OP_Subtract ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageNeverNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageNeverTaken (int /*<<< orphan*/ *) ; 
 scalar_t__ first_valueName ; 
 scalar_t__ lagName ; 
 scalar_t__ leadName ; 
 scalar_t__ nth_valueName ; 
 int sqlite3GetTempReg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int,int,int,int) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  windowCheckIntValue (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void windowReturnOneRow(
  Parse *pParse,
  Window *pMWin,
  int regGosub,
  int addrGosub
){
  Vdbe *v = sqlite3GetVdbe(pParse);
  Window *pWin;
  for(pWin=pMWin; pWin; pWin=pWin->pNextWin){
    FuncDef *pFunc = pWin->pFunc;
    if( pFunc->zName==nth_valueName
     || pFunc->zName==first_valueName
    ){
      int csr = pWin->csrApp;
      int lbl = sqlite3VdbeMakeLabel(pParse);
      int tmpReg = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp2(v, OP_Null, 0, pWin->regResult);

      if( pFunc->zName==nth_valueName ){
        sqlite3VdbeAddOp3(v, OP_Column, pMWin->iEphCsr, pWin->iArgCol+1,tmpReg);
        windowCheckIntValue(pParse, tmpReg, 2);
      }else{
        sqlite3VdbeAddOp2(v, OP_Integer, 1, tmpReg);
      }
      sqlite3VdbeAddOp3(v, OP_Add, tmpReg, pWin->regApp, tmpReg);
      sqlite3VdbeAddOp3(v, OP_Gt, pWin->regApp+1, lbl, tmpReg);
      VdbeCoverageNeverNull(v);
      sqlite3VdbeAddOp3(v, OP_SeekRowid, csr, 0, tmpReg);
      VdbeCoverageNeverTaken(v);
      sqlite3VdbeAddOp3(v, OP_Column, csr, pWin->iArgCol, pWin->regResult);
      sqlite3VdbeResolveLabel(v, lbl);
      sqlite3ReleaseTempReg(pParse, tmpReg);
    }
    else if( pFunc->zName==leadName || pFunc->zName==lagName ){
      int nArg = pWin->pOwner->x.pList->nExpr;
      int iEph = pMWin->iEphCsr;
      int csr = pWin->csrApp;
      int lbl = sqlite3VdbeMakeLabel(pParse);
      int tmpReg = sqlite3GetTempReg(pParse);

      if( nArg<3 ){
        sqlite3VdbeAddOp2(v, OP_Null, 0, pWin->regResult);
      }else{
        sqlite3VdbeAddOp3(v, OP_Column, iEph, pWin->iArgCol+2, pWin->regResult);
      }
      sqlite3VdbeAddOp2(v, OP_Rowid, iEph, tmpReg);
      if( nArg<2 ){
        int val = (pFunc->zName==leadName ? 1 : -1);
        sqlite3VdbeAddOp2(v, OP_AddImm, tmpReg, val);
      }else{
        int op = (pFunc->zName==leadName ? OP_Add : OP_Subtract);
        int tmpReg2 = sqlite3GetTempReg(pParse);
        sqlite3VdbeAddOp3(v, OP_Column, iEph, pWin->iArgCol+1, tmpReg2);
        sqlite3VdbeAddOp3(v, op, tmpReg2, tmpReg, tmpReg);
        sqlite3ReleaseTempReg(pParse, tmpReg2);
      }

      sqlite3VdbeAddOp3(v, OP_SeekRowid, csr, lbl, tmpReg);
      VdbeCoverage(v);
      sqlite3VdbeAddOp3(v, OP_Column, csr, pWin->iArgCol, pWin->regResult);
      sqlite3VdbeResolveLabel(v, lbl);
      sqlite3ReleaseTempReg(pParse, tmpReg);
    }
  }
  sqlite3VdbeAddOp2(v, OP_Gosub, regGosub, addrGosub);
}