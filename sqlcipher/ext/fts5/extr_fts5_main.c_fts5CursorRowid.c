#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_5__ {scalar_t__ ePlan; int /*<<< orphan*/  pExpr; TYPE_1__* pSorter; } ;
struct TYPE_4__ {int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_2__ Fts5Cursor ;

/* Variables and functions */
 scalar_t__ FTS5_PLAN_MATCH ; 
 scalar_t__ FTS5_PLAN_SORTED_MATCH ; 
 scalar_t__ FTS5_PLAN_SOURCE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Fts5ExprRowid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static i64 fts5CursorRowid(Fts5Cursor *pCsr){
  assert( pCsr->ePlan==FTS5_PLAN_MATCH 
       || pCsr->ePlan==FTS5_PLAN_SORTED_MATCH 
       || pCsr->ePlan==FTS5_PLAN_SOURCE 
  );
  if( pCsr->pSorter ){
    return pCsr->pSorter->iRowid;
  }else{
    return sqlite3Fts5ExprRowid(pCsr->pExpr);
  }
}