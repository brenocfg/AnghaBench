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
 int /*<<< orphan*/  CONTENT_EXISTS_STMT ; 
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int content_exists(fulltext_vtab *v){
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, CONTENT_EXISTS_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_step(s);
  if( rc!=SQLITE_ROW ) return rc;

  /* We expect only one row.  We must execute another sqlite3_step()
   * to complete the iteration; otherwise the table will remain locked. */
  rc = sqlite3_step(s);
  if( rc==SQLITE_DONE ) return SQLITE_ROW;
  if( rc==SQLITE_ROW ) return SQLITE_ERROR;
  return rc;
}