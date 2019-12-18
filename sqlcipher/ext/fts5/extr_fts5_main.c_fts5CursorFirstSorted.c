#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_16__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; } ;
struct TYPE_15__ {char* zRank; char* zRankArgs; TYPE_2__* pSorter; int /*<<< orphan*/  pExpr; } ;
struct TYPE_12__ {TYPE_5__* pConfig; } ;
struct TYPE_14__ {TYPE_4__* pSortCsr; TYPE_1__ p; } ;
struct TYPE_13__ {int nIdx; int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_2__ Fts5Sorter ;
typedef  TYPE_3__ Fts5FullTable ;
typedef  TYPE_4__ Fts5Cursor ;
typedef  TYPE_5__ Fts5Config ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5PrepareStatement (int /*<<< orphan*/ *,TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int fts5SorterNext (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int sqlite3Fts5ExprPhraseCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 

__attribute__((used)) static int fts5CursorFirstSorted(
  Fts5FullTable *pTab, 
  Fts5Cursor *pCsr, 
  int bDesc
){
  Fts5Config *pConfig = pTab->p.pConfig;
  Fts5Sorter *pSorter;
  int nPhrase;
  sqlite3_int64 nByte;
  int rc;
  const char *zRank = pCsr->zRank;
  const char *zRankArgs = pCsr->zRankArgs;
  
  nPhrase = sqlite3Fts5ExprPhraseCount(pCsr->pExpr);
  nByte = sizeof(Fts5Sorter) + sizeof(int) * (nPhrase-1);
  pSorter = (Fts5Sorter*)sqlite3_malloc64(nByte);
  if( pSorter==0 ) return SQLITE_NOMEM;
  memset(pSorter, 0, (size_t)nByte);
  pSorter->nIdx = nPhrase;

  /* TODO: It would be better to have some system for reusing statement
  ** handles here, rather than preparing a new one for each query. But that
  ** is not possible as SQLite reference counts the virtual table objects.
  ** And since the statement required here reads from this very virtual 
  ** table, saving it creates a circular reference.
  **
  ** If SQLite a built-in statement cache, this wouldn't be a problem. */
  rc = fts5PrepareStatement(&pSorter->pStmt, pConfig,
      "SELECT rowid, rank FROM %Q.%Q ORDER BY %s(%s%s%s) %s",
      pConfig->zDb, pConfig->zName, zRank, pConfig->zName,
      (zRankArgs ? ", " : ""),
      (zRankArgs ? zRankArgs : ""),
      bDesc ? "DESC" : "ASC"
  );

  pCsr->pSorter = pSorter;
  if( rc==SQLITE_OK ){
    assert( pTab->pSortCsr==0 );
    pTab->pSortCsr = pCsr;
    rc = fts5SorterNext(pCsr);
    pTab->pSortCsr = 0;
  }

  if( rc!=SQLITE_OK ){
    sqlite3_finalize(pSorter->pStmt);
    sqlite3_free(pSorter);
    pCsr->pSorter = 0;
  }

  return rc;
}