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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_2__ {int /*<<< orphan*/  pExplain; int /*<<< orphan*/  zSql; } ;
typedef  TYPE_1__ explain_cursor ;

/* Variables and functions */
 int EXPLN_COLUMN_SQL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int explainColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  explain_cursor *pCur = (explain_cursor*)cur;
  if( i==EXPLN_COLUMN_SQL ){
    sqlite3_result_text(ctx, pCur->zSql, -1, SQLITE_TRANSIENT);
  }else{
    sqlite3_result_value(ctx, sqlite3_column_value(pCur->pExplain, i));
  }
  return SQLITE_OK;
}