#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_3__ {struct TYPE_3__* zSchema; int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_1__ BinfoCursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static int binfoClose(sqlite3_vtab_cursor *pCursor){
  BinfoCursor *pCsr = (BinfoCursor *)pCursor;
  sqlite3_finalize(pCsr->pStmt);
  sqlite3_free(pCsr->zSchema);
  sqlite3_free(pCsr);
  return SQLITE_OK;
}