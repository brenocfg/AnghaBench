#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {int /*<<< orphan*/  n; int /*<<< orphan*/  a; } ;
typedef  int /*<<< orphan*/  Fts3Table ;
typedef  TYPE_1__ Blob ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_STAT_INCRMERGEHINT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  SQL_REPLACE_STAT ; 
 int fts3SqlStmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3IncrmergeHintStore(Fts3Table *p, Blob *pHint){
  sqlite3_stmt *pReplace = 0;
  int rc;                         /* Return code */

  rc = fts3SqlStmt(p, SQL_REPLACE_STAT, &pReplace, 0);
  if( rc==SQLITE_OK ){
    sqlite3_bind_int(pReplace, 1, FTS_STAT_INCRMERGEHINT);
    sqlite3_bind_blob(pReplace, 2, pHint->a, pHint->n, SQLITE_STATIC);
    sqlite3_step(pReplace);
    rc = sqlite3_reset(pReplace);
    sqlite3_bind_null(pReplace, 2);
  }

  return rc;
}