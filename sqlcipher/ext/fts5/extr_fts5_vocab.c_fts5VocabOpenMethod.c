#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_10__ {int /*<<< orphan*/  zErrMsg; } ;
typedef  TYPE_2__ sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_13__ {TYPE_1__* pConfig; } ;
struct TYPE_12__ {int /*<<< orphan*/ * aCnt; int /*<<< orphan*/ * aDoc; int /*<<< orphan*/ * pStmt; TYPE_5__* pFts5; } ;
struct TYPE_11__ {int /*<<< orphan*/  zFts5Tbl; int /*<<< orphan*/  zFts5Db; int /*<<< orphan*/  pGlobal; int /*<<< orphan*/  db; } ;
struct TYPE_9__ {int nCol; } ;
typedef  TYPE_3__ Fts5VocabTable ;
typedef  TYPE_4__ Fts5VocabCursor ;
typedef  TYPE_5__ Fts5Table ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3Fts5FlushToDisk (TYPE_5__*) ; 
 scalar_t__ sqlite3Fts5MallocZero (int*,int) ; 
 char* sqlite3Fts5Mprintf (int*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* sqlite3Fts5TableFromCsrid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5VocabOpenMethod(
  sqlite3_vtab *pVTab, 
  sqlite3_vtab_cursor **ppCsr
){
  Fts5VocabTable *pTab = (Fts5VocabTable*)pVTab;
  Fts5Table *pFts5 = 0;
  Fts5VocabCursor *pCsr = 0;
  int rc = SQLITE_OK;
  sqlite3_stmt *pStmt = 0;
  char *zSql = 0;

  zSql = sqlite3Fts5Mprintf(&rc,
      "SELECT t.%Q FROM %Q.%Q AS t WHERE t.%Q MATCH '*id'",
      pTab->zFts5Tbl, pTab->zFts5Db, pTab->zFts5Tbl, pTab->zFts5Tbl
  );
  if( zSql ){
    rc = sqlite3_prepare_v2(pTab->db, zSql, -1, &pStmt, 0);
  }
  sqlite3_free(zSql);
  assert( rc==SQLITE_OK || pStmt==0 );
  if( rc==SQLITE_ERROR ) rc = SQLITE_OK;

  if( pStmt && sqlite3_step(pStmt)==SQLITE_ROW ){
    i64 iId = sqlite3_column_int64(pStmt, 0);
    pFts5 = sqlite3Fts5TableFromCsrid(pTab->pGlobal, iId);
  }

  if( rc==SQLITE_OK ){
    if( pFts5==0 ){
      rc = sqlite3_finalize(pStmt);
      pStmt = 0;
      if( rc==SQLITE_OK ){
        pVTab->zErrMsg = sqlite3_mprintf(
            "no such fts5 table: %s.%s", pTab->zFts5Db, pTab->zFts5Tbl
            );
        rc = SQLITE_ERROR;
      }
    }else{
      rc = sqlite3Fts5FlushToDisk(pFts5);
    }
  }

  if( rc==SQLITE_OK ){
    int nByte = pFts5->pConfig->nCol * sizeof(i64)*2 + sizeof(Fts5VocabCursor);
    pCsr = (Fts5VocabCursor*)sqlite3Fts5MallocZero(&rc, nByte);
  }

  if( pCsr ){
    pCsr->pFts5 = pFts5;
    pCsr->pStmt = pStmt;
    pCsr->aCnt = (i64*)&pCsr[1];
    pCsr->aDoc = &pCsr->aCnt[pFts5->pConfig->nCol];
  }else{
    sqlite3_finalize(pStmt);
  }

  *ppCsr = (sqlite3_vtab_cursor*)pCsr;
  return rc;
}