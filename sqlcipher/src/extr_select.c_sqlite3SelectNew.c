#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_14__ {int mallocFailed; } ;
struct TYPE_13__ {scalar_t__ nErr; TYPE_6__* db; scalar_t__ nSelect; } ;
struct TYPE_12__ {int* addrOpenEphm; int /*<<< orphan*/ * pSrc; scalar_t__ pWinDefn; scalar_t__ pWin; scalar_t__ pWith; int /*<<< orphan*/ * pLimit; scalar_t__ pNext; scalar_t__ pPrior; int /*<<< orphan*/ * pOrderBy; int /*<<< orphan*/ * pHaving; int /*<<< orphan*/ * pGroupBy; int /*<<< orphan*/ * pWhere; scalar_t__ nSelectRow; scalar_t__ selId; scalar_t__ iOffset; scalar_t__ iLimit; int /*<<< orphan*/  selFlags; int /*<<< orphan*/  op; int /*<<< orphan*/ * pEList; } ;
typedef  int /*<<< orphan*/  SrcList ;
typedef  TYPE_1__ Select ;
typedef  TYPE_2__ Parse ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TK_ASTERISK ; 
 int /*<<< orphan*/  TK_SELECT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clearSelect (TYPE_6__*,TYPE_1__*,int) ; 
 TYPE_1__* sqlite3DbMallocRawNN (TYPE_6__*,int) ; 
 int /*<<< orphan*/ * sqlite3DbMallocZero (TYPE_6__*,int) ; 
 int /*<<< orphan*/  sqlite3Expr (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3ExprListAppend (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Select *sqlite3SelectNew(
  Parse *pParse,        /* Parsing context */
  ExprList *pEList,     /* which columns to include in the result */
  SrcList *pSrc,        /* the FROM clause -- which tables to scan */
  Expr *pWhere,         /* the WHERE clause */
  ExprList *pGroupBy,   /* the GROUP BY clause */
  Expr *pHaving,        /* the HAVING clause */
  ExprList *pOrderBy,   /* the ORDER BY clause */
  u32 selFlags,         /* Flag parameters, such as SF_Distinct */
  Expr *pLimit          /* LIMIT value.  NULL means not used */
){
  Select *pNew;
  Select standin;
  pNew = sqlite3DbMallocRawNN(pParse->db, sizeof(*pNew) );
  if( pNew==0 ){
    assert( pParse->db->mallocFailed );
    pNew = &standin;
  }
  if( pEList==0 ){
    pEList = sqlite3ExprListAppend(pParse, 0,
                                   sqlite3Expr(pParse->db,TK_ASTERISK,0));
  }
  pNew->pEList = pEList;
  pNew->op = TK_SELECT;
  pNew->selFlags = selFlags;
  pNew->iLimit = 0;
  pNew->iOffset = 0;
  pNew->selId = ++pParse->nSelect;
  pNew->addrOpenEphm[0] = -1;
  pNew->addrOpenEphm[1] = -1;
  pNew->nSelectRow = 0;
  if( pSrc==0 ) pSrc = sqlite3DbMallocZero(pParse->db, sizeof(*pSrc));
  pNew->pSrc = pSrc;
  pNew->pWhere = pWhere;
  pNew->pGroupBy = pGroupBy;
  pNew->pHaving = pHaving;
  pNew->pOrderBy = pOrderBy;
  pNew->pPrior = 0;
  pNew->pNext = 0;
  pNew->pLimit = pLimit;
  pNew->pWith = 0;
#ifndef SQLITE_OMIT_WINDOWFUNC
  pNew->pWin = 0;
  pNew->pWinDefn = 0;
#endif
  if( pParse->db->mallocFailed ) {
    clearSelect(pParse->db, pNew, pNew!=&standin);
    pNew = 0;
  }else{
    assert( pNew->pSrc!=0 || pParse->nErr>0 );
  }
  assert( pNew!=&standin );
  return pNew;
}