#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* pRename; } ;
struct TYPE_11__ {int /*<<< orphan*/  pParse; TYPE_1__ u; } ;
typedef  TYPE_3__ Walker ;
struct TYPE_10__ {scalar_t__ pTab; } ;
struct TYPE_13__ {scalar_t__ op; TYPE_2__ y; } ;
struct TYPE_12__ {scalar_t__ pTab; } ;
typedef  TYPE_4__ RenameCtx ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 scalar_t__ TK_COLUMN ; 
 int WRC_Continue ; 
 int /*<<< orphan*/  renameTokenFind (int /*<<< orphan*/ ,TYPE_4__*,void*) ; 

__attribute__((used)) static int renameTableExprCb(Walker *pWalker, Expr *pExpr){
  RenameCtx *p = pWalker->u.pRename;
  if( pExpr->op==TK_COLUMN && p->pTab==pExpr->y.pTab ){
    renameTokenFind(pWalker->pParse, p, (void*)&pExpr->y.pTab);
  }
  return WRC_Continue;
}