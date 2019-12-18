#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zToken; } ;
struct TYPE_6__ {scalar_t__ op; TYPE_1__ u; } ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_Quoted ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_ID ; 
 scalar_t__ TK_STRING ; 
 scalar_t__ TK_TRUEFALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,char*) ; 

int sqlite3ExprIdToTrueFalse(Expr *pExpr){
  assert( pExpr->op==TK_ID || pExpr->op==TK_STRING );
  if( !ExprHasProperty(pExpr, EP_Quoted)
   && (sqlite3StrICmp(pExpr->u.zToken, "true")==0
       || sqlite3StrICmp(pExpr->u.zToken, "false")==0)
  ){
    pExpr->op = TK_TRUEFALSE;
    return 1;
  }
  return 0;
}