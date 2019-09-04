#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_18__ {TYPE_5__* pList; TYPE_3__* pSelect; } ;
struct TYPE_19__ {scalar_t__ op; int iTable; TYPE_6__ x; } ;
struct TYPE_17__ {TYPE_4__* a; } ;
struct TYPE_16__ {TYPE_7__* pExpr; } ;
struct TYPE_15__ {TYPE_2__* pEList; } ;
struct TYPE_14__ {TYPE_1__* a; } ;
struct TYPE_13__ {TYPE_7__* pExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_7__ Expr ;

/* Variables and functions */
 scalar_t__ TK_REGISTER ; 
 scalar_t__ TK_SELECT ; 
 scalar_t__ TK_VECTOR ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3ExprCodeTemp (int /*<<< orphan*/ *,TYPE_7__*,int*) ; 
 TYPE_7__* sqlite3VectorFieldSubexpr (TYPE_7__*,int) ; 

__attribute__((used)) static int exprVectorRegister(
  Parse *pParse,                  /* Parse context */
  Expr *pVector,                  /* Vector to extract element from */
  int iField,                     /* Field to extract from pVector */
  int regSelect,                  /* First in array of registers */
  Expr **ppExpr,                  /* OUT: Expression element */
  int *pRegFree                   /* OUT: Temp register to free */
){
  u8 op = pVector->op;
  assert( op==TK_VECTOR || op==TK_REGISTER || op==TK_SELECT );
  if( op==TK_REGISTER ){
    *ppExpr = sqlite3VectorFieldSubexpr(pVector, iField);
    return pVector->iTable+iField;
  }
  if( op==TK_SELECT ){
    *ppExpr = pVector->x.pSelect->pEList->a[iField].pExpr;
     return regSelect+iField;
  }
  *ppExpr = pVector->x.pList->a[iField].pExpr;
  return sqlite3ExprCodeTemp(pParse, *ppExpr, pRegFree);
}