#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_5__ {int /*<<< orphan*/  base; int /*<<< orphan*/  pExpr; int /*<<< orphan*/  pMIBuffer; int /*<<< orphan*/  aDoclist; } ;
typedef  TYPE_1__ Fts3Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  fts3CursorFinalizeStmt (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts3ExprFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Fts3FreeDeferredTokens (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3Fts3MIBufferFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts3ClearCursor(Fts3Cursor *pCsr){
  fts3CursorFinalizeStmt(pCsr);
  sqlite3Fts3FreeDeferredTokens(pCsr);
  sqlite3_free(pCsr->aDoclist);
  sqlite3Fts3MIBufferFree(pCsr->pMIBuffer);
  sqlite3Fts3ExprFree(pCsr->pExpr);
  memset(&(&pCsr->base)[1], 0, sizeof(Fts3Cursor)-sizeof(sqlite3_vtab_cursor));
}