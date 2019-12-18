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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_4__ {int bIgnoreSavepoint; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQL_SELECT_INDEXES ; 
 int /*<<< orphan*/  SQL_SHIFT_SEGDIR_ENTRY ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3SqlStmt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int*) ; 
 int* sqlite3_realloc (int*,int) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3RepackSegdirLevel(
  Fts3Table *p,                   /* FTS3 table handle */
  sqlite3_int64 iAbsLevel         /* Absolute level to repack */
){
  int rc;                         /* Return code */
  int *aIdx = 0;                  /* Array of remaining idx values */
  int nIdx = 0;                   /* Valid entries in aIdx[] */
  int nAlloc = 0;                 /* Allocated size of aIdx[] */
  int i;                          /* Iterator variable */
  sqlite3_stmt *pSelect = 0;      /* Select statement to read idx values */
  sqlite3_stmt *pUpdate = 0;      /* Update statement to modify idx values */

  rc = fts3SqlStmt(p, SQL_SELECT_INDEXES, &pSelect, 0);
  if( rc==SQLITE_OK ){
    int rc2;
    sqlite3_bind_int64(pSelect, 1, iAbsLevel);
    while( SQLITE_ROW==sqlite3_step(pSelect) ){
      if( nIdx>=nAlloc ){
        int *aNew;
        nAlloc += 16;
        aNew = sqlite3_realloc(aIdx, nAlloc*sizeof(int));
        if( !aNew ){
          rc = SQLITE_NOMEM;
          break;
        }
        aIdx = aNew;
      }
      aIdx[nIdx++] = sqlite3_column_int(pSelect, 0);
    }
    rc2 = sqlite3_reset(pSelect);
    if( rc==SQLITE_OK ) rc = rc2;
  }

  if( rc==SQLITE_OK ){
    rc = fts3SqlStmt(p, SQL_SHIFT_SEGDIR_ENTRY, &pUpdate, 0);
  }
  if( rc==SQLITE_OK ){
    sqlite3_bind_int64(pUpdate, 2, iAbsLevel);
  }

  assert( p->bIgnoreSavepoint==0 );
  p->bIgnoreSavepoint = 1;
  for(i=0; rc==SQLITE_OK && i<nIdx; i++){
    if( aIdx[i]!=i ){
      sqlite3_bind_int(pUpdate, 3, aIdx[i]);
      sqlite3_bind_int(pUpdate, 1, i);
      sqlite3_step(pUpdate);
      rc = sqlite3_reset(pUpdate);
    }
  }
  p->bIgnoreSavepoint = 0;

  sqlite3_free(aIdx);
  return rc;
}