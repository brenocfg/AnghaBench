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
struct TYPE_2__ {int /*<<< orphan*/  pStmt; int /*<<< orphan*/  db; int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_1__ stmt_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_next_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmtNext(sqlite3_vtab_cursor *cur){
  stmt_cursor *pCur = (stmt_cursor*)cur;
  pCur->iRowid++;
  pCur->pStmt = sqlite3_next_stmt(pCur->db, pCur->pStmt);
  return SQLITE_OK;
}