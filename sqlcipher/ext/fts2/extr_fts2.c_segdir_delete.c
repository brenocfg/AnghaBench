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
 int /*<<< orphan*/  SEGDIR_DELETE_STMT ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int block_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int segdir_span (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sql_single_step (int /*<<< orphan*/ *) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int segdir_delete(fulltext_vtab *v, int iLevel){
  sqlite3_stmt *s;
  sqlite_int64 iStartBlockid, iEndBlockid;
  int rc = segdir_span(v, iLevel, &iStartBlockid, &iEndBlockid);
  if( rc!=SQLITE_ROW && rc!=SQLITE_DONE ) return rc;

  if( rc==SQLITE_ROW ){
    rc = block_delete(v, iStartBlockid, iEndBlockid);
    if( rc!=SQLITE_OK ) return rc;
  }

  /* Delete the segment directory itself. */
  rc = sql_get_statement(v, SEGDIR_DELETE_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int64(s, 1, iLevel);
  if( rc!=SQLITE_OK ) return rc;

  return sql_single_step(s);
}