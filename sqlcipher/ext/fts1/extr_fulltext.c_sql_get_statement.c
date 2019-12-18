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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {int /*<<< orphan*/ ** pFulltextStatements; int /*<<< orphan*/  zName; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ fulltext_vtab ;
typedef  size_t fulltext_statement ;

/* Variables and functions */
 size_t MAX_STMT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fulltext_zStatement ; 
 int sql_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sql_get_statement(fulltext_vtab *v, fulltext_statement iStmt,
                             sqlite3_stmt **ppStmt){
  assert( iStmt<MAX_STMT );
  if( v->pFulltextStatements[iStmt]==NULL ){
    int rc = sql_prepare(v->db, v->zName, &v->pFulltextStatements[iStmt],
                         fulltext_zStatement[iStmt]);
    if( rc!=SQLITE_OK ) return rc;
  } else {
    int rc = sqlite3_reset(v->pFulltextStatements[iStmt]);
    if( rc!=SQLITE_OK ) return rc;
  }

  *ppStmt = v->pFulltextStatements[iStmt];
  return SQLITE_OK;
}