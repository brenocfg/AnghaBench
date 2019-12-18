#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_9__ {int /*<<< orphan*/  n; int /*<<< orphan*/  p; } ;
struct TYPE_8__ {TYPE_1__* pConfig; } ;
struct TYPE_7__ {scalar_t__ bColumnsize; } ;
typedef  TYPE_2__ Fts5Storage ;
typedef  TYPE_3__ Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_STMT_REPLACE_DOCSIZE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int fts5StorageGetStmt (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5StorageInsertDocsize(
  Fts5Storage *p,                 /* Storage module to write to */
  i64 iRowid,                     /* id value */
  Fts5Buffer *pBuf                /* sz value */
){
  int rc = SQLITE_OK;
  if( p->pConfig->bColumnsize ){
    sqlite3_stmt *pReplace = 0;
    rc = fts5StorageGetStmt(p, FTS5_STMT_REPLACE_DOCSIZE, &pReplace, 0);
    if( rc==SQLITE_OK ){
      sqlite3_bind_int64(pReplace, 1, iRowid);
      sqlite3_bind_blob(pReplace, 2, pBuf->p, pBuf->n, SQLITE_STATIC);
      sqlite3_step(pReplace);
      rc = sqlite3_reset(pReplace);
      sqlite3_bind_null(pReplace, 2);
    }
  }
  return rc;
}