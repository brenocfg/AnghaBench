#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_5__ {int /*<<< orphan*/  db; int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; } ;
struct TYPE_4__ {TYPE_2__* pConfig; } ;
typedef  TYPE_1__ Fts5Storage ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5StorageCount(Fts5Storage *p, const char *zSuffix, i64 *pnRow){
  Fts5Config *pConfig = p->pConfig;
  char *zSql;
  int rc;

  zSql = sqlite3_mprintf("SELECT count(*) FROM %Q.'%q_%s'", 
      pConfig->zDb, pConfig->zName, zSuffix
  );
  if( zSql==0 ){
    rc = SQLITE_NOMEM;
  }else{
    sqlite3_stmt *pCnt = 0;
    rc = sqlite3_prepare_v2(pConfig->db, zSql, -1, &pCnt, 0);
    if( rc==SQLITE_OK ){
      if( SQLITE_ROW==sqlite3_step(pCnt) ){
        *pnRow = sqlite3_column_int64(pCnt, 0);
      }
      rc = sqlite3_finalize(pCnt);
    }
  }

  sqlite3_free(zSql);
  return rc;
}