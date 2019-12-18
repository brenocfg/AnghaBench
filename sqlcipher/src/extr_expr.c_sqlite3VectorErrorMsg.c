#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* pSelect; } ;
struct TYPE_9__ {int flags; TYPE_3__ x; } ;
struct TYPE_7__ {TYPE_1__* pEList; } ;
struct TYPE_6__ {int /*<<< orphan*/  nExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int EP_xIsSelect ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3SubselectError (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void sqlite3VectorErrorMsg(Parse *pParse, Expr *pExpr){
#ifndef SQLITE_OMIT_SUBQUERY
  if( pExpr->flags & EP_xIsSelect ){
    sqlite3SubselectError(pParse, pExpr->x.pSelect->pEList->nExpr, 1);
  }else
#endif
  {
    sqlite3ErrorMsg(pParse, "row value misused");
  }
}