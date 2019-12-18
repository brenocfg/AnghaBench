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

/* Variables and functions */
 int /*<<< orphan*/  CONTENT_SELECT_STMT ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  free (char*) ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sql_step_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 char* string_dup (char const*) ; 

__attribute__((used)) static int content_select(fulltext_vtab *v, sqlite_int64 iRow,
                          char **pzContent){
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, CONTENT_SELECT_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int64(s, 1, iRow);
  if( rc!=SQLITE_OK ) return rc;

  rc = sql_step_statement(v, CONTENT_SELECT_STMT, &s);
  if( rc!=SQLITE_ROW ) return rc;

  *pzContent = string_dup((const char *)sqlite3_column_text(s, 0));

  /* We expect only one row.  We must execute another sqlite3_step()
   * to complete the iteration; otherwise the table will remain locked. */
  rc = sqlite3_step(s);
  if( rc==SQLITE_DONE ) return SQLITE_OK;

  free(*pzContent);
  return rc;
}