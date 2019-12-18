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
 int /*<<< orphan*/  BLOCK_DELETE_ALL_STMT ; 
 int /*<<< orphan*/  SEGDIR_DELETE_ALL_STMT ; 
 int SQLITE_OK ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sql_single_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int segdir_delete_all(fulltext_vtab *v){
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, SEGDIR_DELETE_ALL_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sql_single_step(s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sql_get_statement(v, BLOCK_DELETE_ALL_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  return sql_single_step(s);
}