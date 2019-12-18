#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_3__ {int /*<<< orphan*/  nData; int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  TERM_INSERT_STMT ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sql_single_step_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int term_insert(fulltext_vtab *v, sqlite_int64 *piRowid,
                       const char *pTerm, int nTerm,
                       int iSegment, DocList *doclist){
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, TERM_INSERT_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  if( piRowid==NULL ){
    rc = sqlite3_bind_null(s, 1);
  }else{
    rc = sqlite3_bind_int64(s, 1, *piRowid);
  }
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_text(s, 2, pTerm, nTerm, SQLITE_STATIC);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int(s, 3, iSegment);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_blob(s, 4, doclist->pData, doclist->nData, SQLITE_STATIC);
  if( rc!=SQLITE_OK ) return rc;

  return sql_single_step_statement(v, TERM_INSERT_STMT, &s);
}