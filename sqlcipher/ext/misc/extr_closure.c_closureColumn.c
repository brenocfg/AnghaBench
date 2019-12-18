#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_6__ {TYPE_2__* pVtab; int /*<<< orphan*/  zParentColumn; int /*<<< orphan*/  zIdColumn; int /*<<< orphan*/  zTableName; TYPE_1__* pCurrent; } ;
typedef  TYPE_3__ closure_cursor ;
struct TYPE_5__ {int /*<<< orphan*/  zParentColumn; int /*<<< orphan*/  zIdColumn; int /*<<< orphan*/  zTableName; } ;
struct TYPE_4__ {int /*<<< orphan*/  iGeneration; int /*<<< orphan*/  id; } ;

/* Variables and functions */
#define  CLOSURE_COL_DEPTH 133 
#define  CLOSURE_COL_ID 132 
#define  CLOSURE_COL_IDCOLUMN 131 
#define  CLOSURE_COL_PARENTCOLUMN 130 
#define  CLOSURE_COL_ROOT 129 
#define  CLOSURE_COL_TABLENAME 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int closureColumn(sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int i){
  closure_cursor *pCur = (closure_cursor*)cur;
  switch( i ){
    case CLOSURE_COL_ID: {
      sqlite3_result_int64(ctx, pCur->pCurrent->id);
      break;
    }
    case CLOSURE_COL_DEPTH: {
      sqlite3_result_int(ctx, pCur->pCurrent->iGeneration);
      break;
    }
    case CLOSURE_COL_ROOT: {
      sqlite3_result_null(ctx);
      break;
    }
    case CLOSURE_COL_TABLENAME: {
      sqlite3_result_text(ctx,
         pCur->zTableName ? pCur->zTableName : pCur->pVtab->zTableName,
         -1, SQLITE_TRANSIENT);
      break;
    }
    case CLOSURE_COL_IDCOLUMN: {
      sqlite3_result_text(ctx,
         pCur->zIdColumn ? pCur->zIdColumn : pCur->pVtab->zIdColumn,
         -1, SQLITE_TRANSIENT);
      break;
    }
    case CLOSURE_COL_PARENTCOLUMN: {
      sqlite3_result_text(ctx,
         pCur->zParentColumn ? pCur->zParentColumn : pCur->pVtab->zParentColumn,
         -1, SQLITE_TRANSIENT);
      break;
    }
  }
  return SQLITE_OK;
}