#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ pVtab; } ;
typedef  TYPE_2__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_17__ {int nCol; } ;
struct TYPE_16__ {scalar_t__ ePlan; int /*<<< orphan*/  pStmt; int /*<<< orphan*/  apRankArg; int /*<<< orphan*/  nRankArg; scalar_t__ pRank; int /*<<< orphan*/  iCsrId; int /*<<< orphan*/  iSpecial; } ;
struct TYPE_13__ {TYPE_5__* pConfig; } ;
struct TYPE_15__ {TYPE_1__ p; } ;
typedef  TYPE_3__ Fts5FullTable ;
typedef  TYPE_4__ Fts5Cursor ;
typedef  TYPE_5__ Fts5Config ;

/* Variables and functions */
 scalar_t__ CsrFlagTest (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_EOF ; 
 scalar_t__ FTS5_PLAN_MATCH ; 
 scalar_t__ FTS5_PLAN_SORTED_MATCH ; 
 scalar_t__ FTS5_PLAN_SOURCE ; 
 scalar_t__ FTS5_PLAN_SPECIAL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5ApiInvoke (scalar_t__,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fts5FindRankFunction (TYPE_4__*) ; 
 int /*<<< orphan*/  fts5IsContentless (TYPE_3__*) ; 
 int /*<<< orphan*/  fts5PoslistBlob (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int fts5SeekCursor (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5ColumnMethod(
  sqlite3_vtab_cursor *pCursor,   /* Cursor to retrieve value from */
  sqlite3_context *pCtx,          /* Context for sqlite3_result_xxx() calls */
  int iCol                        /* Index of column to read value from */
){
  Fts5FullTable *pTab = (Fts5FullTable*)(pCursor->pVtab);
  Fts5Config *pConfig = pTab->p.pConfig;
  Fts5Cursor *pCsr = (Fts5Cursor*)pCursor;
  int rc = SQLITE_OK;
  
  assert( CsrFlagTest(pCsr, FTS5CSR_EOF)==0 );

  if( pCsr->ePlan==FTS5_PLAN_SPECIAL ){
    if( iCol==pConfig->nCol ){
      sqlite3_result_int64(pCtx, pCsr->iSpecial);
    }
  }else

  if( iCol==pConfig->nCol ){
    /* User is requesting the value of the special column with the same name
    ** as the table. Return the cursor integer id number. This value is only
    ** useful in that it may be passed as the first argument to an FTS5
    ** auxiliary function.  */
    sqlite3_result_int64(pCtx, pCsr->iCsrId);
  }else if( iCol==pConfig->nCol+1 ){

    /* The value of the "rank" column. */
    if( pCsr->ePlan==FTS5_PLAN_SOURCE ){
      fts5PoslistBlob(pCtx, pCsr);
    }else if( 
        pCsr->ePlan==FTS5_PLAN_MATCH
     || pCsr->ePlan==FTS5_PLAN_SORTED_MATCH
    ){
      if( pCsr->pRank || SQLITE_OK==(rc = fts5FindRankFunction(pCsr)) ){
        fts5ApiInvoke(pCsr->pRank, pCsr, pCtx, pCsr->nRankArg, pCsr->apRankArg);
      }
    }
  }else if( !fts5IsContentless(pTab) ){
    rc = fts5SeekCursor(pCsr, 1);
    if( rc==SQLITE_OK ){
      sqlite3_result_value(pCtx, sqlite3_column_value(pCsr->pStmt, iCol+1));
    }
  }
  return rc;
}