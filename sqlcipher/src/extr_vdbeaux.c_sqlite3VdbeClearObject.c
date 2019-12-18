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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {int nResColumn; scalar_t__ magic; int nVar; int nScan; TYPE_2__* aScan; TYPE_2__* pDblStr; TYPE_2__* zNormSql; TYPE_2__* zSql; TYPE_2__* aColName; int /*<<< orphan*/  nOp; int /*<<< orphan*/  aOp; TYPE_2__* pFree; TYPE_2__* pVList; TYPE_2__* aVar; TYPE_2__* pProgram; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Vdbe ;
struct TYPE_8__ {struct TYPE_8__* zName; struct TYPE_8__* pNextStr; int /*<<< orphan*/  nOp; int /*<<< orphan*/  aOp; struct TYPE_8__* pNext; } ;
typedef  TYPE_2__ SubProgram ;
typedef  TYPE_2__ DblquoteStr ;

/* Variables and functions */
 int COLNAME_N ; 
 scalar_t__ VDBE_MAGIC_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  releaseMemArray (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vdbeFreeOpArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sqlite3VdbeClearObject(sqlite3 *db, Vdbe *p){
  SubProgram *pSub, *pNext;
  assert( p->db==0 || p->db==db );
  releaseMemArray(p->aColName, p->nResColumn*COLNAME_N);
  for(pSub=p->pProgram; pSub; pSub=pNext){
    pNext = pSub->pNext;
    vdbeFreeOpArray(db, pSub->aOp, pSub->nOp);
    sqlite3DbFree(db, pSub);
  }
  if( p->magic!=VDBE_MAGIC_INIT ){
    releaseMemArray(p->aVar, p->nVar);
    sqlite3DbFree(db, p->pVList);
    sqlite3DbFree(db, p->pFree);
  }
  vdbeFreeOpArray(db, p->aOp, p->nOp);
  sqlite3DbFree(db, p->aColName);
  sqlite3DbFree(db, p->zSql);
#ifdef SQLITE_ENABLE_NORMALIZE
  sqlite3DbFree(db, p->zNormSql);
  {
    DblquoteStr *pThis, *pNext;
    for(pThis=p->pDblStr; pThis; pThis=pNext){
      pNext = pThis->pNextStr;
      sqlite3DbFree(db, pThis);
    }
  }
#endif
#ifdef SQLITE_ENABLE_STMT_SCANSTATUS
  {
    int i;
    for(i=0; i<p->nScan; i++){
      sqlite3DbFree(db, p->aScan[i].zName);
    }
    sqlite3DbFree(db, p->aScan);
  }
#endif
}