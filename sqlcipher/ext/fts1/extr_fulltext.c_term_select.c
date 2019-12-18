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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int /*<<< orphan*/  DL_POSITIONS_OFFSETS ; 
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  TERM_SELECT_STMT ; 
 int /*<<< orphan*/  docListInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sql_step_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int term_select(fulltext_vtab *v, const char *zTerm, int nTerm,
                       sqlite_int64 iFirst,
                       sqlite_int64 *rowid,
                       DocList *out){
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, TERM_SELECT_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_text(s, 1, zTerm, nTerm, SQLITE_TRANSIENT);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int64(s, 2, iFirst);
  if( rc!=SQLITE_OK ) return rc;

  rc = sql_step_statement(v, TERM_SELECT_STMT, &s);
  if( rc!=SQLITE_ROW ) return rc==SQLITE_DONE ? SQLITE_ERROR : rc;

  *rowid = sqlite3_column_int64(s, 0);
  docListInit(out, DL_POSITIONS_OFFSETS,
              sqlite3_column_blob(s, 1), sqlite3_column_bytes(s, 1));

  /* We expect only one row.  We must execute another sqlite3_step()
   * to complete the iteration; otherwise the table will remain locked. */
  rc = sqlite3_step(s);
  return rc==SQLITE_DONE ? SQLITE_OK : rc;
}