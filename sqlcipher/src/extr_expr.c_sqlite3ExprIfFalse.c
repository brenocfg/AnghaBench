#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_25__ {int op; int op2; struct TYPE_25__* pLeft; struct TYPE_25__* pRight; } ;
struct TYPE_24__ {int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int OP_Eq ; 
 int OP_Ge ; 
 int OP_Gt ; 
 int /*<<< orphan*/  OP_IfNot ; 
 int OP_IsNull ; 
 int OP_Le ; 
 int OP_Lt ; 
 int OP_Ne ; 
 int OP_NotNull ; 
 int SQLITE_JUMPIFNULL ; 
 int SQLITE_NULLEQ ; 
#define  TK_AND 143 
#define  TK_BETWEEN 142 
#define  TK_EQ 141 
#define  TK_GE 140 
#define  TK_GT 139 
#define  TK_IN 138 
#define  TK_IS 137 
#define  TK_ISNOT 136 
#define  TK_ISNULL 135 
#define  TK_LE 134 
#define  TK_LT 133 
#define  TK_NE 132 
#define  TK_NOT 131 
#define  TK_NOTNULL 130 
#define  TK_OR 129 
#define  TK_TRUTH 128 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageIf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeCompare (TYPE_1__*,TYPE_2__*,TYPE_2__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  exprAlwaysFalse (TYPE_2__*) ; 
 int /*<<< orphan*/  exprAlwaysTrue (TYPE_2__*) ; 
 int /*<<< orphan*/  exprCodeBetween (TYPE_1__*,TYPE_2__*,int,void (*) (TYPE_1__*,TYPE_2__*,int,int),int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeIN (TYPE_1__*,TYPE_2__*,int,int) ; 
 int sqlite3ExprCodeTemp (TYPE_1__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  sqlite3ExprIfTrue (TYPE_1__*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprIsVector (TYPE_2__*) ; 
 int sqlite3ExprTruthValue (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

void sqlite3ExprIfFalse(Parse *pParse, Expr *pExpr, int dest, int jumpIfNull){
  Vdbe *v = pParse->pVdbe;
  int op = 0;
  int regFree1 = 0;
  int regFree2 = 0;
  int r1, r2;

  assert( jumpIfNull==SQLITE_JUMPIFNULL || jumpIfNull==0 );
  if( NEVER(v==0) ) return; /* Existence of VDBE checked by caller */
  if( pExpr==0 )    return;

  /* The value of pExpr->op and op are related as follows:
  **
  **       pExpr->op            op
  **       ---------          ----------
  **       TK_ISNULL          OP_NotNull
  **       TK_NOTNULL         OP_IsNull
  **       TK_NE              OP_Eq
  **       TK_EQ              OP_Ne
  **       TK_GT              OP_Le
  **       TK_LE              OP_Gt
  **       TK_GE              OP_Lt
  **       TK_LT              OP_Ge
  **
  ** For other values of pExpr->op, op is undefined and unused.
  ** The value of TK_ and OP_ constants are arranged such that we
  ** can compute the mapping above using the following expression.
  ** Assert()s verify that the computation is correct.
  */
  op = ((pExpr->op+(TK_ISNULL&1))^1)-(TK_ISNULL&1);

  /* Verify correct alignment of TK_ and OP_ constants
  */
  assert( pExpr->op!=TK_ISNULL || op==OP_NotNull );
  assert( pExpr->op!=TK_NOTNULL || op==OP_IsNull );
  assert( pExpr->op!=TK_NE || op==OP_Eq );
  assert( pExpr->op!=TK_EQ || op==OP_Ne );
  assert( pExpr->op!=TK_LT || op==OP_Ge );
  assert( pExpr->op!=TK_LE || op==OP_Gt );
  assert( pExpr->op!=TK_GT || op==OP_Le );
  assert( pExpr->op!=TK_GE || op==OP_Lt );

  switch( pExpr->op ){
    case TK_AND: {
      testcase( jumpIfNull==0 );
      sqlite3ExprIfFalse(pParse, pExpr->pLeft, dest, jumpIfNull);
      sqlite3ExprIfFalse(pParse, pExpr->pRight, dest, jumpIfNull);
      break;
    }
    case TK_OR: {
      int d2 = sqlite3VdbeMakeLabel(pParse);
      testcase( jumpIfNull==0 );
      sqlite3ExprIfTrue(pParse, pExpr->pLeft, d2, jumpIfNull^SQLITE_JUMPIFNULL);
      sqlite3ExprIfFalse(pParse, pExpr->pRight, dest, jumpIfNull);
      sqlite3VdbeResolveLabel(v, d2);
      break;
    }
    case TK_NOT: {
      testcase( jumpIfNull==0 );
      sqlite3ExprIfTrue(pParse, pExpr->pLeft, dest, jumpIfNull);
      break;
    }
    case TK_TRUTH: {
      int isNot;   /* IS NOT TRUE or IS NOT FALSE */
      int isTrue;  /* IS TRUE or IS NOT TRUE */
      testcase( jumpIfNull==0 );
      isNot = pExpr->op2==TK_ISNOT;
      isTrue = sqlite3ExprTruthValue(pExpr->pRight);
      testcase( isTrue && isNot );
      testcase( !isTrue && isNot );
      if( isTrue ^ isNot ){
        /* IS TRUE and IS NOT FALSE */
        sqlite3ExprIfFalse(pParse, pExpr->pLeft, dest,
                           isNot ? 0 : SQLITE_JUMPIFNULL);

      }else{
        /* IS FALSE and IS NOT TRUE */
        sqlite3ExprIfTrue(pParse, pExpr->pLeft, dest,
                          isNot ? 0 : SQLITE_JUMPIFNULL);
      }
      break;
    }
    case TK_IS:
    case TK_ISNOT:
      testcase( pExpr->op==TK_IS );
      testcase( pExpr->op==TK_ISNOT );
      op = (pExpr->op==TK_IS) ? TK_NE : TK_EQ;
      jumpIfNull = SQLITE_NULLEQ;
      /* Fall thru */
    case TK_LT:
    case TK_LE:
    case TK_GT:
    case TK_GE:
    case TK_NE:
    case TK_EQ: {
      if( sqlite3ExprIsVector(pExpr->pLeft) ) goto default_expr;
      testcase( jumpIfNull==0 );
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      r2 = sqlite3ExprCodeTemp(pParse, pExpr->pRight, &regFree2);
      codeCompare(pParse, pExpr->pLeft, pExpr->pRight, op,
                  r1, r2, dest, jumpIfNull);
      assert(TK_LT==OP_Lt); testcase(op==OP_Lt); VdbeCoverageIf(v,op==OP_Lt);
      assert(TK_LE==OP_Le); testcase(op==OP_Le); VdbeCoverageIf(v,op==OP_Le);
      assert(TK_GT==OP_Gt); testcase(op==OP_Gt); VdbeCoverageIf(v,op==OP_Gt);
      assert(TK_GE==OP_Ge); testcase(op==OP_Ge); VdbeCoverageIf(v,op==OP_Ge);
      assert(TK_EQ==OP_Eq); testcase(op==OP_Eq);
      VdbeCoverageIf(v, op==OP_Eq && jumpIfNull!=SQLITE_NULLEQ);
      VdbeCoverageIf(v, op==OP_Eq && jumpIfNull==SQLITE_NULLEQ);
      assert(TK_NE==OP_Ne); testcase(op==OP_Ne);
      VdbeCoverageIf(v, op==OP_Ne && jumpIfNull!=SQLITE_NULLEQ);
      VdbeCoverageIf(v, op==OP_Ne && jumpIfNull==SQLITE_NULLEQ);
      testcase( regFree1==0 );
      testcase( regFree2==0 );
      break;
    }
    case TK_ISNULL:
    case TK_NOTNULL: {
      r1 = sqlite3ExprCodeTemp(pParse, pExpr->pLeft, &regFree1);
      sqlite3VdbeAddOp2(v, op, r1, dest);
      testcase( op==TK_ISNULL );   VdbeCoverageIf(v, op==TK_ISNULL);
      testcase( op==TK_NOTNULL );  VdbeCoverageIf(v, op==TK_NOTNULL);
      testcase( regFree1==0 );
      break;
    }
    case TK_BETWEEN: {
      testcase( jumpIfNull==0 );
      exprCodeBetween(pParse, pExpr, dest, sqlite3ExprIfFalse, jumpIfNull);
      break;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case TK_IN: {
      if( jumpIfNull ){
        sqlite3ExprCodeIN(pParse, pExpr, dest, dest);
      }else{
        int destIfNull = sqlite3VdbeMakeLabel(pParse);
        sqlite3ExprCodeIN(pParse, pExpr, dest, destIfNull);
        sqlite3VdbeResolveLabel(v, destIfNull);
      }
      break;
    }
#endif
    default: {
    default_expr: 
      if( exprAlwaysFalse(pExpr) ){
        sqlite3VdbeGoto(v, dest);
      }else if( exprAlwaysTrue(pExpr) ){
        /* no-op */
      }else{
        r1 = sqlite3ExprCodeTemp(pParse, pExpr, &regFree1);
        sqlite3VdbeAddOp3(v, OP_IfNot, r1, dest, jumpIfNull!=0);
        VdbeCoverage(v);
        testcase( regFree1==0 );
        testcase( jumpIfNull==0 );
      }
      break;
    }
  }
  sqlite3ReleaseTempReg(pParse, regFree1);
  sqlite3ReleaseTempReg(pParse, regFree2);
}