#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_1__ stmt_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_STMTSTATUS_FULLSCAN_STEP ; 
 int SQLITE_STMTSTATUS_MEMUSED ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
#define  STMT_COLUMN_BUSY 138 
#define  STMT_COLUMN_MEM 137 
#define  STMT_COLUMN_NAIDX 136 
#define  STMT_COLUMN_NCOL 135 
#define  STMT_COLUMN_NSCAN 134 
#define  STMT_COLUMN_NSORT 133 
#define  STMT_COLUMN_NSTEP 132 
#define  STMT_COLUMN_REPREP 131 
#define  STMT_COLUMN_RO 130 
#define  STMT_COLUMN_RUN 129 
#define  STMT_COLUMN_SQL 128 
 int /*<<< orphan*/  sqlite3_column_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_sql (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_stmt_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_stmt_readonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_stmt_status (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmtColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  stmt_cursor *pCur = (stmt_cursor*)cur;
  switch( i ){
    case STMT_COLUMN_SQL: {
      sqlite3_result_text(ctx, sqlite3_sql(pCur->pStmt), -1, SQLITE_TRANSIENT);
      break;
    }
    case STMT_COLUMN_NCOL: {
      sqlite3_result_int(ctx, sqlite3_column_count(pCur->pStmt));
      break;
    }
    case STMT_COLUMN_RO: {
      sqlite3_result_int(ctx, sqlite3_stmt_readonly(pCur->pStmt));
      break;
    }
    case STMT_COLUMN_BUSY: {
      sqlite3_result_int(ctx, sqlite3_stmt_busy(pCur->pStmt));
      break;
    }
    case STMT_COLUMN_MEM: {
      i = SQLITE_STMTSTATUS_MEMUSED + 
            STMT_COLUMN_NSCAN - SQLITE_STMTSTATUS_FULLSCAN_STEP;
      /* Fall thru */
    }
    case STMT_COLUMN_NSCAN:
    case STMT_COLUMN_NSORT:
    case STMT_COLUMN_NAIDX:
    case STMT_COLUMN_NSTEP:
    case STMT_COLUMN_REPREP:
    case STMT_COLUMN_RUN: {
      sqlite3_result_int(ctx, sqlite3_stmt_status(pCur->pStmt,
                      i-STMT_COLUMN_NSCAN+SQLITE_STMTSTATUS_FULLSCAN_STEP, 0));
      break;
    }
  }
  return SQLITE_OK;
}