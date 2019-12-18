#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_5__ {int nAutoincrmerge; scalar_t__ bFts4; int /*<<< orphan*/  bHasStat; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int FTS3_MERGE_COUNT ; 
 int FTS_STAT_AUTOINCRMERGE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQL_REPLACE_STAT ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3Getint (char const**) ; 
 int fts3SqlStmt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Fts3CreateStatTable (int*,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3DoAutoincrmerge(
  Fts3Table *p,                   /* FTS3 table handle */
  const char *zParam              /* Nul-terminated string containing boolean */
){
  int rc = SQLITE_OK;
  sqlite3_stmt *pStmt = 0;
  p->nAutoincrmerge = fts3Getint(&zParam);
  if( p->nAutoincrmerge==1 || p->nAutoincrmerge>FTS3_MERGE_COUNT ){
    p->nAutoincrmerge = 8;
  }
  if( !p->bHasStat ){
    assert( p->bFts4==0 );
    sqlite3Fts3CreateStatTable(&rc, p);
    if( rc ) return rc;
  }
  rc = fts3SqlStmt(p, SQL_REPLACE_STAT, &pStmt, 0);
  if( rc ) return rc;
  sqlite3_bind_int(pStmt, 1, FTS_STAT_AUTOINCRMERGE);
  sqlite3_bind_int(pStmt, 2, p->nAutoincrmerge);
  sqlite3_step(pStmt);
  rc = sqlite3_reset(pStmt);
  return rc;
}