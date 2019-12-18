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
struct TYPE_3__ {int mxSavepoint; int /*<<< orphan*/  inTransaction; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  TESTONLY (int) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Fts3PendingTermsClear (TYPE_1__*) ; 

__attribute__((used)) static int fts3RollbackToMethod(sqlite3_vtab *pVtab, int iSavepoint){
  Fts3Table *p = (Fts3Table*)pVtab;
  UNUSED_PARAMETER(iSavepoint);
  assert( p->inTransaction );
  TESTONLY( p->mxSavepoint = iSavepoint );
  sqlite3Fts3PendingTermsClear(p);
  return SQLITE_OK;
}