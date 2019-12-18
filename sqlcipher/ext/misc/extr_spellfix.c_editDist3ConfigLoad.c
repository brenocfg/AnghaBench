#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_13__ {int nLang; TYPE_1__* a; } ;
struct TYPE_12__ {struct TYPE_12__* pNext; scalar_t__ a; scalar_t__ iCost; void* nTo; void* nFrom; } ;
struct TYPE_11__ {int iLang; int iInsCost; int iDelCost; int iSubCost; TYPE_2__* pCost; } ;
typedef  TYPE_1__ EditDist3Lang ;
typedef  TYPE_2__ EditDist3Cost ;
typedef  TYPE_3__ EditDist3Config ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  editDist3ConfigClear (TYPE_3__*) ; 
 TYPE_2__* editDist3CostSort (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 TYPE_2__* sqlite3_malloc64 (int) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int sqlite3_prepare (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_1__* sqlite3_realloc64 (TYPE_1__*,int) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int editDist3ConfigLoad(
  EditDist3Config *p,      /* The edit distance configuration to load */
  sqlite3 *db,            /* Load from this database */
  const char *zTable      /* Name of the table from which to load */
){
  sqlite3_stmt *pStmt;
  int rc, rc2;
  char *zSql;
  int iLangPrev = -9999;
  EditDist3Lang *pLang = 0;

  zSql = sqlite3_mprintf("SELECT iLang, cFrom, cTo, iCost"
                         " FROM \"%w\" WHERE iLang>=0 ORDER BY iLang", zTable);
  if( zSql==0 ) return SQLITE_NOMEM;
  rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
  sqlite3_free(zSql);
  if( rc ) return rc;
  editDist3ConfigClear(p);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    int iLang = sqlite3_column_int(pStmt, 0);
    const char *zFrom = (const char*)sqlite3_column_text(pStmt, 1);
    int nFrom = zFrom ? sqlite3_column_bytes(pStmt, 1) : 0;
    const char *zTo = (const char*)sqlite3_column_text(pStmt, 2);
    int nTo = zTo ? sqlite3_column_bytes(pStmt, 2) : 0;
    int iCost = sqlite3_column_int(pStmt, 3);

    assert( zFrom!=0 || nFrom==0 );
    assert( zTo!=0 || nTo==0 );
    if( nFrom>100 || nTo>100 ) continue;
    if( iCost<0 ) continue;
    if( iCost>=10000 ) continue;  /* Costs above 10K are considered infinite */
    if( pLang==0 || iLang!=iLangPrev ){
      EditDist3Lang *pNew;
      pNew = sqlite3_realloc64(p->a, (p->nLang+1)*sizeof(p->a[0]));
      if( pNew==0 ){ rc = SQLITE_NOMEM; break; }
      p->a = pNew;
      pLang = &p->a[p->nLang];
      p->nLang++;
      pLang->iLang = iLang;
      pLang->iInsCost = 100;
      pLang->iDelCost = 100;
      pLang->iSubCost = 150;
      pLang->pCost = 0;
      iLangPrev = iLang;
    }
    if( nFrom==1 && zFrom[0]=='?' && nTo==0 ){
      pLang->iDelCost = iCost;
    }else if( nFrom==0 && nTo==1 && zTo[0]=='?' ){
      pLang->iInsCost = iCost;
    }else if( nFrom==1 && nTo==1 && zFrom[0]=='?' && zTo[0]=='?' ){
      pLang->iSubCost = iCost;
    }else{
      EditDist3Cost *pCost;
      int nExtra = nFrom + nTo - 4;
      if( nExtra<0 ) nExtra = 0;
      pCost = sqlite3_malloc64( sizeof(*pCost) + nExtra );
      if( pCost==0 ){ rc = SQLITE_NOMEM; break; }
      pCost->nFrom = (u8)nFrom;
      pCost->nTo = (u8)nTo;
      pCost->iCost = (u16)iCost;
      memcpy(pCost->a, zFrom, nFrom);
      memcpy(pCost->a + nFrom, zTo, nTo);
      pCost->pNext = pLang->pCost;
      pLang->pCost = pCost; 
    }
  }
  rc2 = sqlite3_finalize(pStmt);
  if( rc==SQLITE_OK ) rc = rc2;
  if( rc==SQLITE_OK ){
    int iLang;
    for(iLang=0; iLang<p->nLang; iLang++){
      p->a[iLang].pCost = editDist3CostSort(p->a[iLang].pCost);
    }
  }
  return rc;
}