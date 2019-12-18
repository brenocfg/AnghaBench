#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ okConstFactor; } ;
typedef  TYPE_1__ Parse ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeAtInit (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3ExprIsConstantNotJoin (int /*<<< orphan*/ *) ; 

void sqlite3ExprCodeFactorable(Parse *pParse, Expr *pExpr, int target){
  if( pParse->okConstFactor && sqlite3ExprIsConstantNotJoin(pExpr) ){
    sqlite3ExprCodeAtInit(pParse, pExpr, target);
  }else{
    sqlite3ExprCode(pParse, pExpr, target);
  }
}