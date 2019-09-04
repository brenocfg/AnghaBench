#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sWalker ;
struct TYPE_7__ {TYPE_3__* pSelect; } ;
struct TYPE_8__ {TYPE_1__ u; int /*<<< orphan*/  xExprCallback; int /*<<< orphan*/ * pParse; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_9__ {int /*<<< orphan*/  pHaving; } ;
typedef  TYPE_3__ Select ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  havingToWhereExprCb ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void havingToWhere(Parse *pParse, Select *p){
  Walker sWalker;
  memset(&sWalker, 0, sizeof(sWalker));
  sWalker.pParse = pParse;
  sWalker.xExprCallback = havingToWhereExprCb;
  sWalker.u.pSelect = p;
  sqlite3WalkExpr(&sWalker, p->pHaving);
#if SELECTTRACE_ENABLED
  if( sWalker.eCode && (sqlite3SelectTrace & 0x100)!=0 ){
    SELECTTRACE(0x100,pParse,p,("Move HAVING terms into WHERE:\n"));
    sqlite3TreeViewSelect(0, p, 0);
  }
#endif
}