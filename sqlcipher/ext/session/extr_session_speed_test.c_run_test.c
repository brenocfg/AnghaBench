#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3_session ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  abort_due_to_error (int) ; 
 int /*<<< orphan*/  execsql (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 int sqlite3_prepare (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 
 int sqlite3changeset_apply (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3session_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3session_changeset (int /*<<< orphan*/ *,int*,void**) ; 
 int sqlite3session_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3session_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xConflict ; 

__attribute__((used)) static void run_test(
  sqlite3 *db, 
  sqlite3 *db2, 
  int nRow, 
  const char *zSql
){
  sqlite3_session *pSession = 0;
  sqlite3_stmt *pStmt = 0;
  int rc;
  int i;
  int nChangeset;
  void *pChangeset;

  /* Attach a session object to database db */
  rc = sqlite3session_create(db, "main", &pSession);
  if( rc!=SQLITE_OK ) abort_due_to_error(rc);

  /* Configure the session to capture changes on all tables */
  rc = sqlite3session_attach(pSession, 0);
  if( rc!=SQLITE_OK ) abort_due_to_error(rc);

  /* Prepare the SQL statement */
  rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
  if( rc!=SQLITE_OK ) abort_due_to_error(rc);

  /* Open a transaction */
  execsql(db, "BEGIN");

  /* Execute the SQL statement nRow times */
  for(i=0; i<nRow; i++){
    sqlite3_bind_int(pStmt, 1, i);
    sqlite3_step(pStmt);
    rc = sqlite3_reset(pStmt);
    if( rc!=SQLITE_OK ) abort_due_to_error(rc);
  }
  sqlite3_finalize(pStmt);

  /* Extract a changeset from the sessions object */
  rc = sqlite3session_changeset(pSession, &nChangeset, &pChangeset);
  if( rc!=SQLITE_OK ) abort_due_to_error(rc);
  execsql(db, "COMMIT");

  /* Apply the changeset to the second db */
  rc = sqlite3changeset_apply(db2, nChangeset, pChangeset, 0, xConflict, 0);
  if( rc!=SQLITE_OK ) abort_due_to_error(rc);

  /* Cleanup */
  sqlite3_free(pChangeset);
  sqlite3session_delete(pSession);
}