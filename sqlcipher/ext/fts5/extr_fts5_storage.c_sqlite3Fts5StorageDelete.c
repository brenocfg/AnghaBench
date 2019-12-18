#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_8__ {scalar_t__ eContent; scalar_t__ bColumnsize; } ;
struct TYPE_7__ {TYPE_2__* pConfig; } ;
typedef  TYPE_1__ Fts5Storage ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_CONTENT_NORMAL ; 
 int /*<<< orphan*/  FTS5_STMT_DELETE_CONTENT ; 
 int /*<<< orphan*/  FTS5_STMT_DELETE_DOCSIZE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5StorageDeleteFromIndex (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int fts5StorageGetStmt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int fts5StorageLoadTotals (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

int sqlite3Fts5StorageDelete(Fts5Storage *p, i64 iDel, sqlite3_value **apVal){
  Fts5Config *pConfig = p->pConfig;
  int rc;
  sqlite3_stmt *pDel = 0;

  assert( pConfig->eContent!=FTS5_CONTENT_NORMAL || apVal==0 );
  rc = fts5StorageLoadTotals(p, 1);

  /* Delete the index records */
  if( rc==SQLITE_OK ){
    rc = fts5StorageDeleteFromIndex(p, iDel, apVal);
  }

  /* Delete the %_docsize record */
  if( rc==SQLITE_OK && pConfig->bColumnsize ){
    rc = fts5StorageGetStmt(p, FTS5_STMT_DELETE_DOCSIZE, &pDel, 0);
    if( rc==SQLITE_OK ){
      sqlite3_bind_int64(pDel, 1, iDel);
      sqlite3_step(pDel);
      rc = sqlite3_reset(pDel);
    }
  }

  /* Delete the %_content record */
  if( pConfig->eContent==FTS5_CONTENT_NORMAL ){
    if( rc==SQLITE_OK ){
      rc = fts5StorageGetStmt(p, FTS5_STMT_DELETE_CONTENT, &pDel, 0);
    }
    if( rc==SQLITE_OK ){
      sqlite3_bind_int64(pDel, 1, iDel);
      sqlite3_step(pDel);
      rc = sqlite3_reset(pDel);
    }
  }

  return rc;
}