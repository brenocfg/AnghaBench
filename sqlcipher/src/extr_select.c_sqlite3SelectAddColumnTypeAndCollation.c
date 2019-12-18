#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct ExprList_item {int /*<<< orphan*/ * pExpr; } ;
struct TYPE_19__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  sNC ;
struct TYPE_20__ {int nCol; int szTabRow; TYPE_7__* aCol; } ;
typedef  TYPE_3__ Table ;
struct TYPE_25__ {int /*<<< orphan*/  zName; } ;
struct TYPE_24__ {scalar_t__ affinity; char const* zName; scalar_t__ zColl; int /*<<< orphan*/  colFlags; } ;
struct TYPE_23__ {int /*<<< orphan*/  pSrcList; } ;
struct TYPE_22__ {TYPE_2__* db; } ;
struct TYPE_21__ {int selFlags; TYPE_1__* pEList; int /*<<< orphan*/  pSrc; } ;
struct TYPE_18__ {int nExpr; struct ExprList_item* a; } ;
typedef  TYPE_4__ Select ;
typedef  TYPE_5__ Parse ;
typedef  TYPE_6__ NameContext ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_7__ Column ;
typedef  TYPE_8__ CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  COLFLAG_HASTYPE ; 
 int SF_Resolved ; 
 scalar_t__ SQLITE_AFF_BLOB ; 
 int /*<<< orphan*/  assert (int) ; 
 char* columnType (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char const*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 char const* sqlite3DbReallocOrFree (TYPE_2__*,char const*,int) ; 
 scalar_t__ sqlite3DbStrDup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3ExprAffinity (int /*<<< orphan*/ *) ; 
 TYPE_8__* sqlite3ExprCollSeq (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int sqlite3Strlen30 (char const*) ; 

void sqlite3SelectAddColumnTypeAndCollation(
  Parse *pParse,        /* Parsing contexts */
  Table *pTab,          /* Add column type information to this table */
  Select *pSelect       /* SELECT used to determine types and collations */
){
  sqlite3 *db = pParse->db;
  NameContext sNC;
  Column *pCol;
  CollSeq *pColl;
  int i;
  Expr *p;
  struct ExprList_item *a;

  assert( pSelect!=0 );
  assert( (pSelect->selFlags & SF_Resolved)!=0 );
  assert( pTab->nCol==pSelect->pEList->nExpr || db->mallocFailed );
  if( db->mallocFailed ) return;
  memset(&sNC, 0, sizeof(sNC));
  sNC.pSrcList = pSelect->pSrc;
  a = pSelect->pEList->a;
  for(i=0, pCol=pTab->aCol; i<pTab->nCol; i++, pCol++){
    const char *zType;
    int n, m;
    p = a[i].pExpr;
    zType = columnType(&sNC, p, 0, 0, 0);
    /* pCol->szEst = ... // Column size est for SELECT tables never used */
    pCol->affinity = sqlite3ExprAffinity(p);
    if( zType ){
      m = sqlite3Strlen30(zType);
      n = sqlite3Strlen30(pCol->zName);
      pCol->zName = sqlite3DbReallocOrFree(db, pCol->zName, n+m+2);
      if( pCol->zName ){
        memcpy(&pCol->zName[n+1], zType, m+1);
        pCol->colFlags |= COLFLAG_HASTYPE;
      }
    }
    if( pCol->affinity==0 ) pCol->affinity = SQLITE_AFF_BLOB;
    pColl = sqlite3ExprCollSeq(pParse, p);
    if( pColl && pCol->zColl==0 ){
      pCol->zColl = sqlite3DbStrDup(db, pColl->zName);
    }
  }
  pTab->szTabRow = 1; /* Any non-zero value works */
}