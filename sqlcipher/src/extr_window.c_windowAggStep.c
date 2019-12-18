#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_14__ {int iArgCol; int iEphCsr; scalar_t__ regStartRowid; scalar_t__ eStart; int regApp; int csrApp; int regAccum; TYPE_4__* pOwner; scalar_t__ pFilter; TYPE_6__* pFunc; struct TYPE_14__* pNextWin; } ;
typedef  TYPE_5__ Window ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_15__ {scalar_t__ zName; int funcFlags; scalar_t__ xSFunc; } ;
struct TYPE_12__ {TYPE_2__* pList; } ;
struct TYPE_13__ {TYPE_3__ x; } ;
struct TYPE_11__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_10__ {int /*<<< orphan*/  pExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_6__ FuncDef ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  OP_AddImm ; 
 int /*<<< orphan*/  OP_AggInverse ; 
 int /*<<< orphan*/  OP_AggStep ; 
 int /*<<< orphan*/  OP_CollSeq ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Delete ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_IfNot ; 
 int /*<<< orphan*/  OP_IsNull ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_SCopy ; 
 int /*<<< orphan*/  OP_SeekGE ; 
 int /*<<< orphan*/  P4_COLLSEQ ; 
 int /*<<< orphan*/  P4_FUNCDEF ; 
 int SQLITE_FUNC_MINMAX ; 
 int SQLITE_FUNC_NEEDCOLL ; 
 scalar_t__ TK_UNBOUNDED ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageNeverTaken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ first_valueName ; 
 scalar_t__ noopStepFunc ; 
 scalar_t__ nth_valueName ; 
 int /*<<< orphan*/ * sqlite3ExprNNCollSeq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3GetTempReg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int windowArgCount (TYPE_5__*) ; 

__attribute__((used)) static void windowAggStep(
  Parse *pParse, 
  Window *pMWin,                  /* Linked list of window functions */
  int csr,                        /* Read arguments from this cursor */
  int bInverse,                   /* True to invoke xInverse instead of xStep */
  int reg                         /* Array of registers */
){
  Vdbe *v = sqlite3GetVdbe(pParse);
  Window *pWin;
  for(pWin=pMWin; pWin; pWin=pWin->pNextWin){
    FuncDef *pFunc = pWin->pFunc;
    int regArg;
    int nArg = windowArgCount(pWin);
    int i;

    for(i=0; i<nArg; i++){
      if( i!=1 || pFunc->zName!=nth_valueName ){
        sqlite3VdbeAddOp3(v, OP_Column, csr, pWin->iArgCol+i, reg+i);
      }else{
        sqlite3VdbeAddOp3(v, OP_Column, pMWin->iEphCsr, pWin->iArgCol+i, reg+i);
      }
    }
    regArg = reg;

    if( pMWin->regStartRowid==0
     && (pFunc->funcFlags & SQLITE_FUNC_MINMAX) 
     && (pWin->eStart!=TK_UNBOUNDED)
    ){
      int addrIsNull = sqlite3VdbeAddOp1(v, OP_IsNull, regArg);
      VdbeCoverage(v);
      if( bInverse==0 ){
        sqlite3VdbeAddOp2(v, OP_AddImm, pWin->regApp+1, 1);
        sqlite3VdbeAddOp2(v, OP_SCopy, regArg, pWin->regApp);
        sqlite3VdbeAddOp3(v, OP_MakeRecord, pWin->regApp, 2, pWin->regApp+2);
        sqlite3VdbeAddOp2(v, OP_IdxInsert, pWin->csrApp, pWin->regApp+2);
      }else{
        sqlite3VdbeAddOp4Int(v, OP_SeekGE, pWin->csrApp, 0, regArg, 1);
        VdbeCoverageNeverTaken(v);
        sqlite3VdbeAddOp1(v, OP_Delete, pWin->csrApp);
        sqlite3VdbeJumpHere(v, sqlite3VdbeCurrentAddr(v)-2);
      }
      sqlite3VdbeJumpHere(v, addrIsNull);
    }else if( pWin->regApp ){
      assert( pFunc->zName==nth_valueName
           || pFunc->zName==first_valueName
      );
      assert( bInverse==0 || bInverse==1 );
      sqlite3VdbeAddOp2(v, OP_AddImm, pWin->regApp+1-bInverse, 1);
    }else if( pFunc->xSFunc!=noopStepFunc ){
      int addrIf = 0;
      if( pWin->pFilter ){
        int regTmp;
        assert( nArg==0 || nArg==pWin->pOwner->x.pList->nExpr );
        assert( nArg || pWin->pOwner->x.pList==0 );
        regTmp = sqlite3GetTempReg(pParse);
        sqlite3VdbeAddOp3(v, OP_Column, csr, pWin->iArgCol+nArg,regTmp);
        addrIf = sqlite3VdbeAddOp3(v, OP_IfNot, regTmp, 0, 1);
        VdbeCoverage(v);
        sqlite3ReleaseTempReg(pParse, regTmp);
      }
      if( pFunc->funcFlags & SQLITE_FUNC_NEEDCOLL ){
        CollSeq *pColl;
        assert( nArg>0 );
        pColl = sqlite3ExprNNCollSeq(pParse, pWin->pOwner->x.pList->a[0].pExpr);
        sqlite3VdbeAddOp4(v, OP_CollSeq, 0,0,0, (const char*)pColl, P4_COLLSEQ);
      }
      sqlite3VdbeAddOp3(v, bInverse? OP_AggInverse : OP_AggStep, 
                        bInverse, regArg, pWin->regAccum);
      sqlite3VdbeAppendP4(v, pFunc, P4_FUNCDEF);
      sqlite3VdbeChangeP5(v, (u8)nArg);
      if( addrIf ) sqlite3VdbeJumpHere(v, addrIf);
    }
  }
}