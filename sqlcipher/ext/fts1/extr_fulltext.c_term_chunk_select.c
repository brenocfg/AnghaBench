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
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
#define  SQLITE_INTEGER 129 
#define  SQLITE_NULL 128 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  TERM_CHUNK_SELECT_STMT ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sql_step_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int term_chunk_select(fulltext_vtab *v, const char *zTerm, int nTerm,
                           sqlite_int64 iFirst, sqlite_int64 *piResult){
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, TERM_CHUNK_SELECT_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_text(s, 1, zTerm, nTerm, SQLITE_STATIC);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int64(s, 2, iFirst);
  if( rc!=SQLITE_OK ) return rc;

  rc = sql_step_statement(v, TERM_CHUNK_SELECT_STMT, &s);
  if( rc!=SQLITE_ROW ) return rc==SQLITE_DONE ? SQLITE_ERROR : rc;

  switch( sqlite3_column_type(s, 0) ){
    case SQLITE_NULL:
      rc = SQLITE_DONE;
      break;
    case SQLITE_INTEGER:
     *piResult = sqlite3_column_int64(s, 0);
     break;
    default:
      return SQLITE_ERROR;
  }
  /* We expect only one row.  We must execute another sqlite3_step()
   * to complete the iteration; otherwise the table will remain locked. */
  if( sqlite3_step(s) != SQLITE_DONE ) return SQLITE_ERROR;
  return rc;
}