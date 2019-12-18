#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ pVtab; } ;
struct TYPE_15__ {scalar_t__ pStmt; int pExpr; TYPE_1__ base; } ;
struct TYPE_12__ {scalar_t__ zErrMsg; } ;
struct TYPE_13__ {TYPE_2__ base; } ;
struct TYPE_14__ {TYPE_3__ p; int /*<<< orphan*/  pStorage; } ;
typedef  TYPE_4__ Fts5FullTable ;
typedef  TYPE_5__ Fts5Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  CsrFlagClear (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int CsrFlagTest (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_REQUIRE_CONTENT ; 
 int FTS5_CORRUPT ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5CursorRowid (TYPE_5__*) ; 
 int fts5StmtType (TYPE_5__*) ; 
 int sqlite3Fts5StorageStmt (int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (scalar_t__) ; 
 int sqlite3_step (scalar_t__) ; 

__attribute__((used)) static int fts5SeekCursor(Fts5Cursor *pCsr, int bErrormsg){
  int rc = SQLITE_OK;

  /* If the cursor does not yet have a statement handle, obtain one now. */ 
  if( pCsr->pStmt==0 ){
    Fts5FullTable *pTab = (Fts5FullTable*)(pCsr->base.pVtab);
    int eStmt = fts5StmtType(pCsr);
    rc = sqlite3Fts5StorageStmt(
        pTab->pStorage, eStmt, &pCsr->pStmt, (bErrormsg?&pTab->p.base.zErrMsg:0)
    );
    assert( rc!=SQLITE_OK || pTab->p.base.zErrMsg==0 );
    assert( CsrFlagTest(pCsr, FTS5CSR_REQUIRE_CONTENT) );
  }

  if( rc==SQLITE_OK && CsrFlagTest(pCsr, FTS5CSR_REQUIRE_CONTENT) ){
    assert( pCsr->pExpr );
    sqlite3_reset(pCsr->pStmt);
    sqlite3_bind_int64(pCsr->pStmt, 1, fts5CursorRowid(pCsr));
    rc = sqlite3_step(pCsr->pStmt);
    if( rc==SQLITE_ROW ){
      rc = SQLITE_OK;
      CsrFlagClear(pCsr, FTS5CSR_REQUIRE_CONTENT);
    }else{
      rc = sqlite3_reset(pCsr->pStmt);
      if( rc==SQLITE_OK ){
        rc = FTS5_CORRUPT;
      }
    }
  }
  return rc;
}