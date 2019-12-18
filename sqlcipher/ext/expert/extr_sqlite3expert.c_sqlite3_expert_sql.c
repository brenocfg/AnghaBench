#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* pStatement; int /*<<< orphan*/ * pScan; int /*<<< orphan*/  dbv; scalar_t__ bRun; } ;
typedef  TYPE_1__ sqlite3expert ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_7__ {char* zSql; scalar_t__ iId; struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ IdxStatement ;
typedef  int /*<<< orphan*/  IdxScan ;

/* Variables and functions */
 int SQLITE_MISUSE ; 
 int SQLITE_OK ; 
 int STRLEN (char const*) ; 
 int /*<<< orphan*/  idxDatabaseError (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ idxMalloc (int*,int) ; 
 int /*<<< orphan*/  idxScanFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idxStatementFree (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **,char const**) ; 
 char* sqlite3_sql (int /*<<< orphan*/ *) ; 

int sqlite3_expert_sql(
  sqlite3expert *p,               /* From sqlite3_expert_new() */
  const char *zSql,               /* SQL statement to add */
  char **pzErr                    /* OUT: Error message (if any) */
){
  IdxScan *pScanOrig = p->pScan;
  IdxStatement *pStmtOrig = p->pStatement;
  int rc = SQLITE_OK;
  const char *zStmt = zSql;

  if( p->bRun ) return SQLITE_MISUSE;

  while( rc==SQLITE_OK && zStmt && zStmt[0] ){
    sqlite3_stmt *pStmt = 0;
    rc = sqlite3_prepare_v2(p->dbv, zStmt, -1, &pStmt, &zStmt);
    if( rc==SQLITE_OK ){
      if( pStmt ){
        IdxStatement *pNew;
        const char *z = sqlite3_sql(pStmt);
        int n = STRLEN(z);
        pNew = (IdxStatement*)idxMalloc(&rc, sizeof(IdxStatement) + n+1);
        if( rc==SQLITE_OK ){
          pNew->zSql = (char*)&pNew[1];
          memcpy(pNew->zSql, z, n+1);
          pNew->pNext = p->pStatement;
          if( p->pStatement ) pNew->iId = p->pStatement->iId+1;
          p->pStatement = pNew;
        }
        sqlite3_finalize(pStmt);
      }
    }else{
      idxDatabaseError(p->dbv, pzErr);
    }
  }

  if( rc!=SQLITE_OK ){
    idxScanFree(p->pScan, pScanOrig);
    idxStatementFree(p->pStatement, pStmtOrig);
    p->pScan = pScanOrig;
    p->pStatement = pStmtOrig;
  }

  return rc;
}