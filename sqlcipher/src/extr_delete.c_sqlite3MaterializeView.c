#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_1__* aDb; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_21__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  pSchema; } ;
typedef  TYPE_4__ Table ;
struct TYPE_23__ {TYPE_3__* db; } ;
struct TYPE_22__ {int nSrc; TYPE_2__* a; } ;
struct TYPE_19__ {scalar_t__ pOn; scalar_t__ pUsing; void* zDatabase; void* zName; } ;
struct TYPE_18__ {int /*<<< orphan*/  zDbSName; } ;
typedef  TYPE_5__ SrcList ;
typedef  int /*<<< orphan*/  SelectDest ;
typedef  int /*<<< orphan*/  Select ;
typedef  TYPE_6__ Parse ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  SF_IncludeHidden ; 
 int /*<<< orphan*/  SRT_EphemTab ; 
 int /*<<< orphan*/  assert (int) ; 
 void* sqlite3DbStrDup (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3ExprDup (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3SchemaToIndex (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Select (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3SelectDelete (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3SelectDestInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sqlite3SelectNew (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* sqlite3SrcListAppend (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sqlite3MaterializeView(
  Parse *pParse,       /* Parsing context */
  Table *pView,        /* View definition */
  Expr *pWhere,        /* Optional WHERE clause to be added */
  ExprList *pOrderBy,  /* Optional ORDER BY clause */
  Expr *pLimit,        /* Optional LIMIT clause */
  int iCur             /* Cursor number for ephemeral table */
){
  SelectDest dest;
  Select *pSel;
  SrcList *pFrom;
  sqlite3 *db = pParse->db;
  int iDb = sqlite3SchemaToIndex(db, pView->pSchema);
  pWhere = sqlite3ExprDup(db, pWhere, 0);
  pFrom = sqlite3SrcListAppend(pParse, 0, 0, 0);
  if( pFrom ){
    assert( pFrom->nSrc==1 );
    pFrom->a[0].zName = sqlite3DbStrDup(db, pView->zName);
    pFrom->a[0].zDatabase = sqlite3DbStrDup(db, db->aDb[iDb].zDbSName);
    assert( pFrom->a[0].pOn==0 );
    assert( pFrom->a[0].pUsing==0 );
  }
  pSel = sqlite3SelectNew(pParse, 0, pFrom, pWhere, 0, 0, pOrderBy, 
                          SF_IncludeHidden, pLimit);
  sqlite3SelectDestInit(&dest, SRT_EphemTab, iCur);
  sqlite3Select(pParse, pSel, &dest);
  sqlite3SelectDelete(db, pSel);
}