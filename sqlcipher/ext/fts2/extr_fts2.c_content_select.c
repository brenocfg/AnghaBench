#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_4__ {int nColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENT_SELECT_STMT ; 
 int SQLITE_DONE ; 
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  freeStringArray (int,char const**) ; 
 int sql_get_statement (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_type (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 char* string_dup (char*) ; 

__attribute__((used)) static int content_select(fulltext_vtab *v, sqlite_int64 iRow,
                          const char ***pValues){
  sqlite3_stmt *s;
  const char **values;
  int i;
  int rc;

  *pValues = NULL;

  rc = sql_get_statement(v, CONTENT_SELECT_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int64(s, 1, iRow);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_step(s);
  if( rc!=SQLITE_ROW ) return rc;

  values = (const char **) sqlite3_malloc(v->nColumn * sizeof(const char *));
  for(i=0; i<v->nColumn; ++i){
    if( sqlite3_column_type(s, i)==SQLITE_NULL ){
      values[i] = NULL;
    }else{
      values[i] = string_dup((char*)sqlite3_column_text(s, i));
    }
  }

  /* We expect only one row.  We must execute another sqlite3_step()
   * to complete the iteration; otherwise the table will remain locked. */
  rc = sqlite3_step(s);
  if( rc==SQLITE_DONE ){
    *pValues = values;
    return SQLITE_OK;
  }

  freeStringArray(v->nColumn, values);
  return rc;
}