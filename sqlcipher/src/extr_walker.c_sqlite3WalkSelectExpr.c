#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_1__ Walker ;
struct TYPE_9__ {int /*<<< orphan*/  pWinDefn; int /*<<< orphan*/  pLimit; int /*<<< orphan*/  pOrderBy; int /*<<< orphan*/  pHaving; int /*<<< orphan*/  pGroupBy; int /*<<< orphan*/  pWhere; int /*<<< orphan*/  pEList; } ;
typedef  TYPE_2__ Select ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 scalar_t__ IN_RENAME_OBJECT ; 
 int WRC_Abort ; 
 int WRC_Continue ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3WalkExpr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3WalkExprList (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int walkWindowList (TYPE_1__*,int /*<<< orphan*/ ) ; 

int sqlite3WalkSelectExpr(Walker *pWalker, Select *p){
  if( sqlite3WalkExprList(pWalker, p->pEList) ) return WRC_Abort;
  if( sqlite3WalkExpr(pWalker, p->pWhere) ) return WRC_Abort;
  if( sqlite3WalkExprList(pWalker, p->pGroupBy) ) return WRC_Abort;
  if( sqlite3WalkExpr(pWalker, p->pHaving) ) return WRC_Abort;
  if( sqlite3WalkExprList(pWalker, p->pOrderBy) ) return WRC_Abort;
  if( sqlite3WalkExpr(pWalker, p->pLimit) ) return WRC_Abort;
#if !defined(SQLITE_OMIT_WINDOWFUNC) && !defined(SQLITE_OMIT_ALTERTABLE)
  {
    Parse *pParse = pWalker->pParse;
    if( pParse && IN_RENAME_OBJECT ){
      int rc = walkWindowList(pWalker, p->pWinDefn);
      assert( rc==WRC_Continue );
      return rc;
    }
  }
#endif
  return WRC_Continue;
}