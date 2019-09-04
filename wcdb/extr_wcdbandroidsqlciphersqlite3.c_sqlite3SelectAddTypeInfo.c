#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pParse; int /*<<< orphan*/  xExprCallback; int /*<<< orphan*/  xSelectCallback2; int /*<<< orphan*/  xSelectCallback; } ;
typedef  TYPE_1__ Walker ;
typedef  int /*<<< orphan*/  Select ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  selectAddSubqueryTypeInfo ; 
 int /*<<< orphan*/  sqlite3ExprWalkNoop ; 
 int /*<<< orphan*/  sqlite3SelectWalkNoop ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqlite3SelectAddTypeInfo(Parse *pParse, Select *pSelect){
#ifndef SQLITE_OMIT_SUBQUERY
  Walker w;
  w.xSelectCallback = sqlite3SelectWalkNoop;
  w.xSelectCallback2 = selectAddSubqueryTypeInfo;
  w.xExprCallback = sqlite3ExprWalkNoop;
  w.pParse = pParse;
  sqlite3WalkSelect(&w, pSelect);
#endif
}