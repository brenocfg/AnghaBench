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
struct TYPE_8__ {scalar_t__ eStart; scalar_t__ regApp; scalar_t__ csrApp; scalar_t__ regAccum; TYPE_3__* pFunc; struct TYPE_8__* pNextWin; } ;
typedef  TYPE_1__ Window ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_10__ {scalar_t__ zName; int funcFlags; } ;
struct TYPE_9__ {int nMem; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ FuncDef ;

/* Variables and functions */
 int MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_ResetSorter ; 
 int SQLITE_FUNC_MINMAX ; 
 scalar_t__ TK_UNBOUNDED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ first_valueName ; 
 scalar_t__ nth_valueName ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  windowArgCount (TYPE_1__*) ; 

__attribute__((used)) static int windowInitAccum(Parse *pParse, Window *pMWin){
  Vdbe *v = sqlite3GetVdbe(pParse);
  int regArg;
  int nArg = 0;
  Window *pWin;
  for(pWin=pMWin; pWin; pWin=pWin->pNextWin){
    FuncDef *pFunc = pWin->pFunc;
    sqlite3VdbeAddOp2(v, OP_Null, 0, pWin->regAccum);
    nArg = MAX(nArg, windowArgCount(pWin));
    if( pFunc->zName==nth_valueName
     || pFunc->zName==first_valueName
    ){
      sqlite3VdbeAddOp2(v, OP_Integer, 0, pWin->regApp);
      sqlite3VdbeAddOp2(v, OP_Integer, 0, pWin->regApp+1);
    }

    if( (pFunc->funcFlags & SQLITE_FUNC_MINMAX) && pWin->csrApp ){
      assert( pWin->eStart!=TK_UNBOUNDED );
      sqlite3VdbeAddOp1(v, OP_ResetSorter, pWin->csrApp);
      sqlite3VdbeAddOp2(v, OP_Integer, 0, pWin->regApp+1);
    }
  }
  regArg = pParse->nMem+1;
  pParse->nMem += nArg;
  return regArg;
}