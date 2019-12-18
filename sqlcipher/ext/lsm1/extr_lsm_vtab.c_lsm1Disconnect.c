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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_3__ {int /*<<< orphan*/  pDb; } ;
typedef  TYPE_1__ lsm1_vtab ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  lsm_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static int lsm1Disconnect(sqlite3_vtab *pVtab){
  lsm1_vtab *p = (lsm1_vtab*)pVtab;
  lsm_close(p->pDb);
  sqlite3_free(p);
  return SQLITE_OK;
}