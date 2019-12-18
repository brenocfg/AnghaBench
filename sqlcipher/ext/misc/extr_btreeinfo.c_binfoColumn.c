#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* pVtab; } ;
typedef  TYPE_2__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_8__ {scalar_t__ hasRowid; scalar_t__ nPage; scalar_t__ depth; int /*<<< orphan*/  zSchema; int /*<<< orphan*/  nEntry; int /*<<< orphan*/  pStmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  zErrMsg; } ;
typedef  TYPE_3__ BinfoCursor ;

/* Variables and functions */
#define  BINFO_COLUMN_DEPTH 137 
#define  BINFO_COLUMN_HASROWID 136 
#define  BINFO_COLUMN_NAME 135 
#define  BINFO_COLUMN_NENTRY 134 
#define  BINFO_COLUMN_NPAGE 133 
#define  BINFO_COLUMN_ROOTPAGE 132 
#define  BINFO_COLUMN_SCHEMA 131 
#define  BINFO_COLUMN_SQL 130 
 int BINFO_COLUMN_SZPAGE ; 
#define  BINFO_COLUMN_TBL_NAME 129 
#define  BINFO_COLUMN_TYPE 128 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int binfoCompute (int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int sqlite3_column_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int binfoColumn(
  sqlite3_vtab_cursor *pCursor, 
  sqlite3_context *ctx, 
  int i
){
  BinfoCursor *pCsr = (BinfoCursor *)pCursor;
  if( i>=BINFO_COLUMN_HASROWID && i<=BINFO_COLUMN_SZPAGE && pCsr->hasRowid<0 ){
    int pgno = sqlite3_column_int(pCsr->pStmt, BINFO_COLUMN_ROOTPAGE+1);
    sqlite3 *db = sqlite3_context_db_handle(ctx);
    int rc = binfoCompute(db, pgno, pCsr);
    if( rc ){
      pCursor->pVtab->zErrMsg = sqlite3_mprintf("%s", sqlite3_errmsg(db));
      return SQLITE_ERROR;
    }
  }
  switch( i ){
    case BINFO_COLUMN_NAME:
    case BINFO_COLUMN_TYPE:
    case BINFO_COLUMN_TBL_NAME:
    case BINFO_COLUMN_ROOTPAGE:
    case BINFO_COLUMN_SQL: {
      sqlite3_result_value(ctx, sqlite3_column_value(pCsr->pStmt, i+1));
      break;
    }
    case BINFO_COLUMN_HASROWID: {
      sqlite3_result_int(ctx, pCsr->hasRowid);
      break;
    }
    case BINFO_COLUMN_NENTRY: {
      sqlite3_result_int64(ctx, pCsr->nEntry);
      break;
    }
    case BINFO_COLUMN_NPAGE: {
      sqlite3_result_int(ctx, pCsr->nPage);
      break;
    }
    case BINFO_COLUMN_DEPTH: {
      sqlite3_result_int(ctx, pCsr->depth);
      break;
    }
    case BINFO_COLUMN_SCHEMA: {
      sqlite3_result_text(ctx, pCsr->zSchema, -1, SQLITE_STATIC);
      break;
    }
  }
  return SQLITE_OK;
}