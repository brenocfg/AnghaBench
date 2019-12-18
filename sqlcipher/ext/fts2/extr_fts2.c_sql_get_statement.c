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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_5__ {int /*<<< orphan*/ ** pFulltextStatements; int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ fulltext_vtab ;
typedef  size_t fulltext_statement ;

/* Variables and functions */
#define  CONTENT_INSERT_STMT 129 
#define  CONTENT_UPDATE_STMT 128 
 size_t MAX_STMT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 char* contentInsertStatement (TYPE_1__*) ; 
 char* contentUpdateStatement (TYPE_1__*) ; 
 char const** fulltext_zStatement ; 
 int sql_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sql_get_statement(fulltext_vtab *v, fulltext_statement iStmt,
                             sqlite3_stmt **ppStmt){
  assert( iStmt<MAX_STMT );
  if( v->pFulltextStatements[iStmt]==NULL ){
    const char *zStmt;
    int rc;
    switch( iStmt ){
      case CONTENT_INSERT_STMT:
        zStmt = contentInsertStatement(v); break;
      case CONTENT_UPDATE_STMT:
        zStmt = contentUpdateStatement(v); break;
      default:
        zStmt = fulltext_zStatement[iStmt];
    }
    rc = sql_prepare(v->db, v->zDb, v->zName, &v->pFulltextStatements[iStmt],
                         zStmt);
    if( zStmt != fulltext_zStatement[iStmt]) sqlite3_free((void *) zStmt);
    if( rc!=SQLITE_OK ) return rc;
  } else {
    int rc = sqlite3_reset(v->pFulltextStatements[iStmt]);
    if( rc!=SQLITE_OK ) return rc;
  }

  *ppStmt = v->pFulltextStatements[iStmt];
  return SQLITE_OK;
}