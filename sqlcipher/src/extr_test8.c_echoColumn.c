#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pVtab; } ;
typedef  TYPE_1__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  echo_vtab ;
struct TYPE_5__ {int /*<<< orphan*/ * pStmt; } ;
typedef  TYPE_2__ echo_cursor ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ simulateVtabError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ *,int) ; 
 int sqlite3_data_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int echoColumn(sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int i){
  int iCol = i + 1;
  sqlite3_stmt *pStmt = ((echo_cursor *)cur)->pStmt;

  if( simulateVtabError((echo_vtab *)(cur->pVtab), "xColumn") ){
    return SQLITE_ERROR;
  }

  if( !pStmt ){
    sqlite3_result_null(ctx);
  }else{
    assert( sqlite3_data_count(pStmt)>iCol );
    sqlite3_result_value(ctx, sqlite3_column_value(pStmt, iCol));
  }
  return SQLITE_OK;
}