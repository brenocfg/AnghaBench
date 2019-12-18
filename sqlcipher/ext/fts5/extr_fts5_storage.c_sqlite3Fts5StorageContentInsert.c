#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_7__ {scalar_t__ eContent; int nCol; int /*<<< orphan*/  db; } ;
struct TYPE_6__ {TYPE_2__* pConfig; } ;
typedef  TYPE_1__ Fts5Storage ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_CONTENT_NORMAL ; 
 int /*<<< orphan*/  FTS5_STMT_INSERT_CONTENT ; 
 scalar_t__ SQLITE_INTEGER ; 
 int SQLITE_OK ; 
 int fts5StorageGetStmt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int fts5StorageNewRowid (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sqlite3_bind_value (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_last_insert_rowid (int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

int sqlite3Fts5StorageContentInsert(
  Fts5Storage *p, 
  sqlite3_value **apVal, 
  i64 *piRowid
){
  Fts5Config *pConfig = p->pConfig;
  int rc = SQLITE_OK;

  /* Insert the new row into the %_content table. */
  if( pConfig->eContent!=FTS5_CONTENT_NORMAL ){
    if( sqlite3_value_type(apVal[1])==SQLITE_INTEGER ){
      *piRowid = sqlite3_value_int64(apVal[1]);
    }else{
      rc = fts5StorageNewRowid(p, piRowid);
    }
  }else{
    sqlite3_stmt *pInsert = 0;    /* Statement to write %_content table */
    int i;                        /* Counter variable */
    rc = fts5StorageGetStmt(p, FTS5_STMT_INSERT_CONTENT, &pInsert, 0);
    for(i=1; rc==SQLITE_OK && i<=pConfig->nCol+1; i++){
      rc = sqlite3_bind_value(pInsert, i, apVal[i]);
    }
    if( rc==SQLITE_OK ){
      sqlite3_step(pInsert);
      rc = sqlite3_reset(pInsert);
    }
    *piRowid = sqlite3_last_insert_rowid(pConfig->db);
  }

  return rc;
}