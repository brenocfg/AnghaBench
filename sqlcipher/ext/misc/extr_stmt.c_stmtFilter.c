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
struct TYPE_2__ {scalar_t__ iRowid; scalar_t__ pStmt; } ;
typedef  TYPE_1__ stmt_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;

/* Variables and functions */
 int stmtNext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stmtFilter(
  sqlite3_vtab_cursor *pVtabCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  stmt_cursor *pCur = (stmt_cursor *)pVtabCursor;
  pCur->pStmt = 0;
  pCur->iRowid = 0;
  return stmtNext(pVtabCursor);
}