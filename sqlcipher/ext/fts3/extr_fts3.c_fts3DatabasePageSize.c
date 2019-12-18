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
struct TYPE_3__ {int nPgsz; int /*<<< orphan*/  db; int /*<<< orphan*/  zDb; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_AUTH ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int sqlite3_prepare (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts3DatabasePageSize(int *pRc, Fts3Table *p){
  if( *pRc==SQLITE_OK ){
    int rc;                       /* Return code */
    char *zSql;                   /* SQL text "PRAGMA %Q.page_size" */
    sqlite3_stmt *pStmt;          /* Compiled "PRAGMA %Q.page_size" statement */
  
    zSql = sqlite3_mprintf("PRAGMA %Q.page_size", p->zDb);
    if( !zSql ){
      rc = SQLITE_NOMEM;
    }else{
      rc = sqlite3_prepare(p->db, zSql, -1, &pStmt, 0);
      if( rc==SQLITE_OK ){
        sqlite3_step(pStmt);
        p->nPgsz = sqlite3_column_int(pStmt, 0);
        rc = sqlite3_finalize(pStmt);
      }else if( rc==SQLITE_AUTH ){
        p->nPgsz = 1024;
        rc = SQLITE_OK;
      }
    }
    assert( p->nPgsz>0 || rc!=SQLITE_OK );
    sqlite3_free(zSql);
    *pRc = rc;
  }
}