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
struct TYPE_9__ {int flags; int /*<<< orphan*/  pLeft; TYPE_3__ x; } ;
struct TYPE_7__ {TYPE_1__* pEList; } ;
struct TYPE_6__ {int nExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int EP_xIsSelect ; 
 int sqlite3ExprVectorSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SubselectError (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3VectorErrorMsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sqlite3ExprCheckIN(Parse *pParse, Expr *pIn){
  int nVector = sqlite3ExprVectorSize(pIn->pLeft);
  if( (pIn->flags & EP_xIsSelect) ){
    if( nVector!=pIn->x.pSelect->pEList->nExpr ){
      sqlite3SubselectError(pParse, pIn->x.pSelect->pEList->nExpr, nVector);
      return 1;
    }
  }else if( nVector!=1 ){
    sqlite3VectorErrorMsg(pParse, pIn->pLeft);
    return 1;
  }
  return 0;
}