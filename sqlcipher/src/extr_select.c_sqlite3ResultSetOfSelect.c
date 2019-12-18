#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_19__ {int bDisable; } ;
struct TYPE_20__ {scalar_t__ mallocFailed; TYPE_1__ lookaside; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_21__ {int nTabRef; int nRowLogEst; int iPKey; int /*<<< orphan*/  aCol; int /*<<< orphan*/  nCol; scalar_t__ zName; } ;
typedef  TYPE_3__ Table ;
struct TYPE_23__ {scalar_t__ nErr; TYPE_2__* db; } ;
struct TYPE_22__ {int /*<<< orphan*/  pEList; struct TYPE_22__* pPrior; } ;
typedef  TYPE_4__ Select ;
typedef  TYPE_5__ Parse ;

/* Variables and functions */
 scalar_t__ SQLITE_FullColNames ; 
 int /*<<< orphan*/  SQLITE_ShortColNames ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ColumnsFromExprList (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* sqlite3DbMallocZero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3DeleteTable (TYPE_2__*,TYPE_3__*) ; 
 int sqlite3LogEst (int) ; 
 int /*<<< orphan*/  sqlite3SelectAddColumnTypeAndCollation (TYPE_5__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3SelectPrep (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

Table *sqlite3ResultSetOfSelect(Parse *pParse, Select *pSelect){
  Table *pTab;
  sqlite3 *db = pParse->db;
  u64 savedFlags;

  savedFlags = db->flags;
  db->flags &= ~(u64)SQLITE_FullColNames;
  db->flags |= SQLITE_ShortColNames;
  sqlite3SelectPrep(pParse, pSelect, 0);
  db->flags = savedFlags;
  if( pParse->nErr ) return 0;
  while( pSelect->pPrior ) pSelect = pSelect->pPrior;
  pTab = sqlite3DbMallocZero(db, sizeof(Table) );
  if( pTab==0 ){
    return 0;
  }
  /* The sqlite3ResultSetOfSelect() is only used n contexts where lookaside
  ** is disabled */
  assert( db->lookaside.bDisable );
  pTab->nTabRef = 1;
  pTab->zName = 0;
  pTab->nRowLogEst = 200; assert( 200==sqlite3LogEst(1048576) );
  sqlite3ColumnsFromExprList(pParse, pSelect->pEList, &pTab->nCol, &pTab->aCol);
  sqlite3SelectAddColumnTypeAndCollation(pParse, pTab, pSelect);
  pTab->iPKey = -1;
  if( db->mallocFailed ){
    sqlite3DeleteTable(db, pTab);
    return 0;
  }
  return pTab;
}