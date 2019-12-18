#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_6__ {TYPE_1__* pConfig; } ;
struct TYPE_5__ {int nCol; int /*<<< orphan*/  bColumnsize; } ;
typedef  TYPE_2__ Fts5Storage ;

/* Variables and functions */
 int FTS5_CORRUPT ; 
 int /*<<< orphan*/  FTS5_STMT_LOOKUP_DOCSIZE ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ fts5StorageDecodeSizeArray (int*,int,int /*<<< orphan*/  const*,int) ; 
 int fts5StorageGetStmt (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

int sqlite3Fts5StorageDocsize(Fts5Storage *p, i64 iRowid, int *aCol){
  int nCol = p->pConfig->nCol;    /* Number of user columns in table */
  sqlite3_stmt *pLookup = 0;      /* Statement to query %_docsize */
  int rc;                         /* Return Code */

  assert( p->pConfig->bColumnsize );
  rc = fts5StorageGetStmt(p, FTS5_STMT_LOOKUP_DOCSIZE, &pLookup, 0);
  if( rc==SQLITE_OK ){
    int bCorrupt = 1;
    sqlite3_bind_int64(pLookup, 1, iRowid);
    if( SQLITE_ROW==sqlite3_step(pLookup) ){
      const u8 *aBlob = sqlite3_column_blob(pLookup, 0);
      int nBlob = sqlite3_column_bytes(pLookup, 0);
      if( 0==fts5StorageDecodeSizeArray(aCol, nCol, aBlob, nBlob) ){
        bCorrupt = 0;
      }
    }
    rc = sqlite3_reset(pLookup);
    if( bCorrupt && rc==SQLITE_OK ){
      rc = FTS5_CORRUPT;
    }
  }

  return rc;
}