#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_6__ {TYPE_1__* pVtab; } ;
typedef  TYPE_2__ closure_cursor ;
struct TYPE_5__ {int /*<<< orphan*/  nCursor; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  closureClearCursor (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static int closureClose(sqlite3_vtab_cursor *cur){
  closure_cursor *pCur = (closure_cursor *)cur;
  closureClearCursor(pCur);
  pCur->pVtab->nCursor--;
  sqlite3_free(pCur);
  return SQLITE_OK;
}