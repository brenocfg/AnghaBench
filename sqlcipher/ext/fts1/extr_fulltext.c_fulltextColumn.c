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
struct TYPE_2__ {int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_1__ fulltext_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fulltextColumn(sqlite3_vtab_cursor *pCursor,
                          sqlite3_context *pContext, int idxCol){
  fulltext_cursor *c = (fulltext_cursor *) pCursor;
  const char *s;

  assert( idxCol==0 );
  s = (const char *) sqlite3_column_text(c->pStmt, 1);
  sqlite3_result_text(pContext, s, -1, SQLITE_TRANSIENT);

  return SQLITE_OK;
}