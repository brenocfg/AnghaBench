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
struct TYPE_3__ {int /*<<< orphan*/  pStorage; } ;
typedef  TYPE_1__ Fts5FullTable ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_ROLLBACK ; 
 int /*<<< orphan*/  fts5CheckTransactionState (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3Fts5StorageRollback (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5RollbackMethod(sqlite3_vtab *pVtab){
  int rc;
  Fts5FullTable *pTab = (Fts5FullTable*)pVtab;
  fts5CheckTransactionState(pTab, FTS5_ROLLBACK, 0);
  rc = sqlite3Fts5StorageRollback(pTab->pStorage);
  return rc;
}