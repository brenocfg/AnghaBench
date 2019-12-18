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
struct TYPE_2__ {int /*<<< orphan*/  pColumnList; int /*<<< orphan*/  pTableList; int /*<<< orphan*/  pDbList; } ;
typedef  TYPE_1__ schema_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int schemaColumn(sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int i){
  schema_cursor *pCur = (schema_cursor *)cur;
  switch( i ){
    case 0:
      sqlite3_result_value(ctx, sqlite3_column_value(pCur->pDbList, 1));
      break;
    case 1:
      sqlite3_result_value(ctx, sqlite3_column_value(pCur->pTableList, 0));
      break;
    default:
      sqlite3_result_value(ctx, sqlite3_column_value(pCur->pColumnList, i-2));
      break;
  }
  return SQLITE_OK;
}