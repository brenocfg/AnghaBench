#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  xExprCallback; int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_10__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_8__ {scalar_t__ zName; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_3__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  renameUnmapExprCb ; 
 int /*<<< orphan*/  sqlite3RenameTokenRemap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sqlite3WalkExprList (TYPE_2__*,TYPE_3__*) ; 

void sqlite3RenameExprlistUnmap(Parse *pParse, ExprList *pEList){
  if( pEList ){
    int i;
    Walker sWalker;
    memset(&sWalker, 0, sizeof(Walker));
    sWalker.pParse = pParse;
    sWalker.xExprCallback = renameUnmapExprCb;
    sqlite3WalkExprList(&sWalker, pEList);
    for(i=0; i<pEList->nExpr; i++){
      sqlite3RenameTokenRemap(pParse, 0, (void*)pEList->a[i].zName);
    }
  }
}