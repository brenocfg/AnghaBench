#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_27__ {int regReturn; int iAddr; } ;
struct TYPE_28__ {TYPE_3__ sub; } ;
struct TYPE_25__ {TYPE_6__* pSelect; } ;
struct TYPE_32__ {scalar_t__ op; int iTable; TYPE_4__ y; TYPE_1__ x; } ;
struct TYPE_31__ {int nMem; int /*<<< orphan*/  db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_30__ {scalar_t__ iLimit; TYPE_13__* pLimit; TYPE_2__* pEList; int /*<<< orphan*/  selId; } ;
struct TYPE_29__ {int iSdst; int iSDParm; int nSdst; int /*<<< orphan*/  eDest; } ;
struct TYPE_26__ {int nExpr; } ;
struct TYPE_24__ {TYPE_8__* pLeft; } ;
typedef  TYPE_5__ SelectDest ;
typedef  TYPE_6__ Select ;
typedef  TYPE_7__ Parse ;
typedef  TYPE_8__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_NoReduce ; 
 int /*<<< orphan*/  EP_Subrtn ; 
 int /*<<< orphan*/  EP_VarSelect ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 int /*<<< orphan*/  ExplainQueryPlan (TYPE_7__*) ; 
 int ExprHasProperty (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExprSetVVAProperty (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_Gosub ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_Once ; 
 int /*<<< orphan*/  OP_Return ; 
 int /*<<< orphan*/  SRT_Exists ; 
 int /*<<< orphan*/  SRT_Mem ; 
 scalar_t__ TK_EXISTS ; 
 int /*<<< orphan*/  TK_INTEGER ; 
 int /*<<< orphan*/  TK_LIMIT ; 
 scalar_t__ TK_SELECT ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_8__* sqlite3ExprAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/ * sqlite3IntTokens ; 
 TYPE_13__* sqlite3PExpr (TYPE_7__*,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3Select (TYPE_7__*,TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3SelectDestInit (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP1 (int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

int sqlite3CodeSubselect(Parse *pParse, Expr *pExpr){
  int addrOnce = 0;           /* Address of OP_Once at top of subroutine */
  int rReg = 0;               /* Register storing resulting */
  Select *pSel;               /* SELECT statement to encode */
  SelectDest dest;            /* How to deal with SELECT result */
  int nReg;                   /* Registers to allocate */
  Expr *pLimit;               /* New limit expression */

  Vdbe *v = pParse->pVdbe;
  assert( v!=0 );
  testcase( pExpr->op==TK_EXISTS );
  testcase( pExpr->op==TK_SELECT );
  assert( pExpr->op==TK_EXISTS || pExpr->op==TK_SELECT );
  assert( ExprHasProperty(pExpr, EP_xIsSelect) );
  pSel = pExpr->x.pSelect;

  /* The evaluation of the EXISTS/SELECT must be repeated every time it
  ** is encountered if any of the following is true:
  **
  **    *  The right-hand side is a correlated subquery
  **    *  The right-hand side is an expression list containing variables
  **    *  We are inside a trigger
  **
  ** If all of the above are false, then we can run this code just once
  ** save the results, and reuse the same result on subsequent invocations.
  */
  if( !ExprHasProperty(pExpr, EP_VarSelect) ){
    /* If this routine has already been coded, then invoke it as a
    ** subroutine. */
    if( ExprHasProperty(pExpr, EP_Subrtn) ){
      ExplainQueryPlan((pParse, 0, "REUSE SUBQUERY %d", pSel->selId));
      sqlite3VdbeAddOp2(v, OP_Gosub, pExpr->y.sub.regReturn,
                        pExpr->y.sub.iAddr);
      return pExpr->iTable;
    }

    /* Begin coding the subroutine */
    ExprSetProperty(pExpr, EP_Subrtn);
    pExpr->y.sub.regReturn = ++pParse->nMem;
    pExpr->y.sub.iAddr =
      sqlite3VdbeAddOp2(v, OP_Integer, 0, pExpr->y.sub.regReturn) + 1;
    VdbeComment((v, "return address"));

    addrOnce = sqlite3VdbeAddOp0(v, OP_Once); VdbeCoverage(v);
  }
  
  /* For a SELECT, generate code to put the values for all columns of
  ** the first row into an array of registers and return the index of
  ** the first register.
  **
  ** If this is an EXISTS, write an integer 0 (not exists) or 1 (exists)
  ** into a register and return that register number.
  **
  ** In both cases, the query is augmented with "LIMIT 1".  Any 
  ** preexisting limit is discarded in place of the new LIMIT 1.
  */
  ExplainQueryPlan((pParse, 1, "%sSCALAR SUBQUERY %d",
        addrOnce?"":"CORRELATED ", pSel->selId));
  nReg = pExpr->op==TK_SELECT ? pSel->pEList->nExpr : 1;
  sqlite3SelectDestInit(&dest, 0, pParse->nMem+1);
  pParse->nMem += nReg;
  if( pExpr->op==TK_SELECT ){
    dest.eDest = SRT_Mem;
    dest.iSdst = dest.iSDParm;
    dest.nSdst = nReg;
    sqlite3VdbeAddOp3(v, OP_Null, 0, dest.iSDParm, dest.iSDParm+nReg-1);
    VdbeComment((v, "Init subquery result"));
  }else{
    dest.eDest = SRT_Exists;
    sqlite3VdbeAddOp2(v, OP_Integer, 0, dest.iSDParm);
    VdbeComment((v, "Init EXISTS result"));
  }
  pLimit = sqlite3ExprAlloc(pParse->db, TK_INTEGER,&sqlite3IntTokens[1], 0);
  if( pSel->pLimit ){
    sqlite3ExprDelete(pParse->db, pSel->pLimit->pLeft);
    pSel->pLimit->pLeft = pLimit;
  }else{
    pSel->pLimit = sqlite3PExpr(pParse, TK_LIMIT, pLimit, 0);
  }
  pSel->iLimit = 0;
  if( sqlite3Select(pParse, pSel, &dest) ){
    return 0;
  }
  pExpr->iTable = rReg = dest.iSDParm;
  ExprSetVVAProperty(pExpr, EP_NoReduce);
  if( addrOnce ){
    sqlite3VdbeJumpHere(v, addrOnce);

    /* Subroutine return */
    sqlite3VdbeAddOp1(v, OP_Return, pExpr->y.sub.regReturn);
    sqlite3VdbeChangeP1(v, pExpr->y.sub.iAddr-1, sqlite3VdbeCurrentAddr(v)-1);
  }

  return rReg;
}