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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_5__ {int nColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENT_INSERT_STMT ; 
 int SQLITE_OK ; 
 int sql_get_statement (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sql_single_step_statement (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_value (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int content_insert(fulltext_vtab *v, sqlite3_value *rowid,
                          sqlite3_value **pValues){
  sqlite3_stmt *s;
  int i;
  int rc = sql_get_statement(v, CONTENT_INSERT_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_value(s, 1, rowid);
  if( rc!=SQLITE_OK ) return rc;

  for(i=0; i<v->nColumn; ++i){
    rc = sqlite3_bind_value(s, 2+i, pValues[i]);
    if( rc!=SQLITE_OK ) return rc;
  }

  return sql_single_step_statement(v, CONTENT_INSERT_STMT, &s);
}