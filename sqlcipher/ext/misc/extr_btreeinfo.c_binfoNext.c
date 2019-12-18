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
struct TYPE_2__ {scalar_t__ rc; int hasRowid; int /*<<< orphan*/  pStmt; } ;
typedef  TYPE_1__ BinfoCursor ;

/* Variables and functions */
 scalar_t__ SQLITE_ERROR ; 
 int SQLITE_OK ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int binfoNext(sqlite3_vtab_cursor *pCursor){
  BinfoCursor *pCsr = (BinfoCursor *)pCursor;
  pCsr->rc = sqlite3_step(pCsr->pStmt);
  pCsr->hasRowid = -1;
  return pCsr->rc==SQLITE_ERROR ? SQLITE_ERROR : SQLITE_OK;
}