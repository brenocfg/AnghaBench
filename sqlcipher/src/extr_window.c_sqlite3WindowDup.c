#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_6__ {int /*<<< orphan*/ * pOwner; void* pEnd; void* pStart; int /*<<< orphan*/  eExclude; int /*<<< orphan*/  eStart; int /*<<< orphan*/  eEnd; int /*<<< orphan*/  eFrmType; void* pOrderBy; void* pPartition; int /*<<< orphan*/  pFunc; void* pFilter; int /*<<< orphan*/  zName; } ;
typedef  TYPE_1__ Window ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_1__*) ; 
 TYPE_1__* sqlite3DbMallocZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3DbStrDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* sqlite3ExprDup (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 void* sqlite3ExprListDup (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

Window *sqlite3WindowDup(sqlite3 *db, Expr *pOwner, Window *p){
  Window *pNew = 0;
  if( ALWAYS(p) ){
    pNew = sqlite3DbMallocZero(db, sizeof(Window));
    if( pNew ){
      pNew->zName = sqlite3DbStrDup(db, p->zName);
      pNew->pFilter = sqlite3ExprDup(db, p->pFilter, 0);
      pNew->pFunc = p->pFunc;
      pNew->pPartition = sqlite3ExprListDup(db, p->pPartition, 0);
      pNew->pOrderBy = sqlite3ExprListDup(db, p->pOrderBy, 0);
      pNew->eFrmType = p->eFrmType;
      pNew->eEnd = p->eEnd;
      pNew->eStart = p->eStart;
      pNew->eExclude = p->eExclude;
      pNew->pStart = sqlite3ExprDup(db, p->pStart, 0);
      pNew->pEnd = sqlite3ExprDup(db, p->pEnd, 0);
      pNew->pOwner = pOwner;
    }
  }
  return pNew;
}