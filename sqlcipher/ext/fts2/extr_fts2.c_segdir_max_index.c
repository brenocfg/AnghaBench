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
typedef  int /*<<< orphan*/  fulltext_vtab ;

/* Variables and functions */
 int /*<<< orphan*/  SEGDIR_MAX_INDEX_STMT ; 
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int segdir_max_index(fulltext_vtab *v, int iLevel, int *pidx){
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, SEGDIR_MAX_INDEX_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int(s, 1, iLevel);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_step(s);
  /* Should always get at least one row due to how max() works. */
  if( rc==SQLITE_DONE ) return SQLITE_DONE;
  if( rc!=SQLITE_ROW ) return rc;

  /* NULL means that there were no inputs to max(). */
  if( SQLITE_NULL==sqlite3_column_type(s, 0) ){
    rc = sqlite3_step(s);
    if( rc==SQLITE_ROW ) return SQLITE_ERROR;
    return rc;
  }

  *pidx = sqlite3_column_int(s, 0);

  /* We expect only one row.  We must execute another sqlite3_step()
   * to complete the iteration; otherwise the table will remain locked. */
  rc = sqlite3_step(s);
  if( rc==SQLITE_ROW ) return SQLITE_ERROR;
  if( rc!=SQLITE_DONE ) return rc;
  return SQLITE_ROW;
}