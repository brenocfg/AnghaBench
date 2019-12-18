#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_6__ {int nColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;
struct TYPE_7__ {int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_2__ fulltext_cursor ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 TYPE_1__* cursor_vtab (TYPE_2__*) ; 
 int /*<<< orphan*/ * sqlite3_column_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,TYPE_2__**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fulltextColumn(sqlite3_vtab_cursor *pCursor,
                          sqlite3_context *pContext, int idxCol){
  fulltext_cursor *c = (fulltext_cursor *) pCursor;
  fulltext_vtab *v = cursor_vtab(c);

  if( idxCol<v->nColumn ){
    sqlite3_value *pVal = sqlite3_column_value(c->pStmt, idxCol+1);
    sqlite3_result_value(pContext, pVal);
  }else if( idxCol==v->nColumn ){
    /* The extra column whose name is the same as the table.
    ** Return a blob which is a pointer to the cursor
    */
    sqlite3_result_blob(pContext, &c, sizeof(c), SQLITE_TRANSIENT);
  }
  return SQLITE_OK;
}