#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mallocFailed; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_8__ {TYPE_1__* db; } ;
typedef  TYPE_2__ Parse ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3ExprDup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3ExprCodeCopy(Parse *pParse, Expr *pExpr, int target){
  sqlite3 *db = pParse->db;
  pExpr = sqlite3ExprDup(db, pExpr, 0);
  if( !db->mallocFailed ) sqlite3ExprCode(pParse, pExpr, target);
  sqlite3ExprDelete(db, pExpr);
}