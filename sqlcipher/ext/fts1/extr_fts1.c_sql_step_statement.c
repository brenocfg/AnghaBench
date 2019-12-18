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
struct TYPE_3__ {int /*<<< orphan*/ ** pFulltextStatements; } ;
typedef  TYPE_1__ fulltext_vtab ;
typedef  size_t fulltext_statement ;

/* Variables and functions */
 size_t MAX_STMT ; 
 int SQLITE_BUSY ; 
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sql_step_statement(fulltext_vtab *v, fulltext_statement iStmt,
                              sqlite3_stmt **ppStmt){
  int rc;
  sqlite3_stmt *s = *ppStmt;
  assert( iStmt<MAX_STMT );
  assert( s==v->pFulltextStatements[iStmt] );

  while( (rc=sqlite3_step(s))!=SQLITE_DONE && rc!=SQLITE_ROW ){
    if( rc==SQLITE_BUSY ) continue;
    if( rc!=SQLITE_ERROR ) return rc;

    /* If an SQLITE_SCHEMA error has occurred, then finalizing this
     * statement is going to delete the fulltext_vtab structure. If
     * the statement just executed is in the pFulltextStatements[]
     * array, it will be finalized twice. So remove it before
     * calling sqlite3_finalize().
     */
    v->pFulltextStatements[iStmt] = NULL;
    rc = sqlite3_finalize(s);
    break;
  }
  return rc;

 err:
  sqlite3_finalize(s);
  return rc;
}