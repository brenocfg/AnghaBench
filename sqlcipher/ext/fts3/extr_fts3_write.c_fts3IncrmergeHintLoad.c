#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_4__ {int n; int /*<<< orphan*/  a; } ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  TYPE_1__ Blob ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_STAT_INCRMERGEHINT ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQL_SELECT_STAT ; 
 int /*<<< orphan*/  blobGrowBuffer (TYPE_1__*,int,int*) ; 
 int fts3SqlStmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3IncrmergeHintLoad(Fts3Table *p, Blob *pHint){
  sqlite3_stmt *pSelect = 0;
  int rc;

  pHint->n = 0;
  rc = fts3SqlStmt(p, SQL_SELECT_STAT, &pSelect, 0);
  if( rc==SQLITE_OK ){
    int rc2;
    sqlite3_bind_int(pSelect, 1, FTS_STAT_INCRMERGEHINT);
    if( SQLITE_ROW==sqlite3_step(pSelect) ){
      const char *aHint = sqlite3_column_blob(pSelect, 0);
      int nHint = sqlite3_column_bytes(pSelect, 0);
      if( aHint ){
        blobGrowBuffer(pHint, nHint, &rc);
        if( rc==SQLITE_OK ){
          memcpy(pHint->a, aHint, nHint);
          pHint->n = nHint;
        }
      }
    }
    rc2 = sqlite3_reset(pSelect);
    if( rc==SQLITE_OK ) rc = rc2;
  }

  return rc;
}