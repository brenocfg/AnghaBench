#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ eStart; TYPE_4__* pFunc; int /*<<< orphan*/  regResult; int /*<<< orphan*/  regAccum; scalar_t__ regApp; int /*<<< orphan*/  csrApp; struct TYPE_5__* pNextWin; } ;
typedef  TYPE_1__ Window ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_6__ {int funcFlags; } ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_AggFinal ; 
 int /*<<< orphan*/  OP_AggValue ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_Last ; 
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_ResetSorter ; 
 int /*<<< orphan*/  P4_FUNCDEF ; 
 int SQLITE_FUNC_MINMAX ; 
 scalar_t__ TK_UNBOUNDED ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  windowArgCount (TYPE_1__*) ; 

__attribute__((used)) static void windowAggFinal(Parse *pParse, Window *pMWin, int bFinal){
  Vdbe *v = sqlite3GetVdbe(pParse);
  Window *pWin;

  for(pWin=pMWin; pWin; pWin=pWin->pNextWin){
    if( (pWin->pFunc->funcFlags & SQLITE_FUNC_MINMAX) 
     && pWin->eStart!=TK_UNBOUNDED 
    ){
      sqlite3VdbeAddOp2(v, OP_Null, 0, pWin->regResult);
      sqlite3VdbeAddOp1(v, OP_Last, pWin->csrApp);
      VdbeCoverage(v);
      sqlite3VdbeAddOp3(v, OP_Column, pWin->csrApp, 0, pWin->regResult);
      sqlite3VdbeJumpHere(v, sqlite3VdbeCurrentAddr(v)-2);
      if( bFinal ){
        sqlite3VdbeAddOp1(v, OP_ResetSorter, pWin->csrApp);
      }
    }else if( pWin->regApp ){
    }else{
      if( bFinal ){
        sqlite3VdbeAddOp2(v, OP_AggFinal, pWin->regAccum, windowArgCount(pWin));
        sqlite3VdbeAppendP4(v, pWin->pFunc, P4_FUNCDEF);
        sqlite3VdbeAddOp2(v, OP_Copy, pWin->regAccum, pWin->regResult);
        sqlite3VdbeAddOp2(v, OP_Null, 0, pWin->regAccum);
      }else{
        sqlite3VdbeAddOp3(v, OP_AggValue, pWin->regAccum, windowArgCount(pWin),
                             pWin->regResult);
        sqlite3VdbeAppendP4(v, pWin->pFunc, P4_FUNCDEF);
      }
    }
  }
}