#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_5__* pList; TYPE_3__* pSelect; } ;
struct TYPE_18__ {scalar_t__ op2; scalar_t__ op; TYPE_6__ x; } ;
struct TYPE_16__ {TYPE_4__* a; } ;
struct TYPE_15__ {TYPE_7__* pExpr; } ;
struct TYPE_14__ {TYPE_2__* pEList; } ;
struct TYPE_13__ {TYPE_1__* a; } ;
struct TYPE_12__ {TYPE_7__* pExpr; } ;
typedef  TYPE_7__ Expr ;

/* Variables and functions */
 scalar_t__ TK_REGISTER ; 
 scalar_t__ TK_SELECT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3ExprIsVector (TYPE_7__*) ; 
 int sqlite3ExprVectorSize (TYPE_7__*) ; 

Expr *sqlite3VectorFieldSubexpr(Expr *pVector, int i){
  assert( i<sqlite3ExprVectorSize(pVector) );
  if( sqlite3ExprIsVector(pVector) ){
    assert( pVector->op2==0 || pVector->op==TK_REGISTER );
    if( pVector->op==TK_SELECT || pVector->op2==TK_SELECT ){
      return pVector->x.pSelect->pEList->a[i].pExpr;
    }else{
      return pVector->x.pList->a[i].pExpr;
    }
  }
  return pVector;
}