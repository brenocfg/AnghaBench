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
struct TYPE_3__ {int /*<<< orphan*/  pLsmCur; struct TYPE_3__* pKey2; } ;
typedef  TYPE_1__ lsm1_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  lsm_csr_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static int lsm1Close(sqlite3_vtab_cursor *cur){
  lsm1_cursor *pCur = (lsm1_cursor*)cur;
  sqlite3_free(pCur->pKey2);
  lsm_csr_close(pCur->pLsmCur);
  sqlite3_free(pCur);
  return SQLITE_OK;
}