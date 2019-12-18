#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  Fts5Table ;
typedef  int /*<<< orphan*/  Fts5FullTable ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_SAVEPOINT ; 
 int /*<<< orphan*/  UNUSED_PARAM (int) ; 
 int /*<<< orphan*/  fts5CheckTransactionState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3Fts5FlushToDisk (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5SavepointMethod(sqlite3_vtab *pVtab, int iSavepoint){
  UNUSED_PARAM(iSavepoint);  /* Call below is a no-op for NDEBUG builds */
  fts5CheckTransactionState((Fts5FullTable*)pVtab, FTS5_SAVEPOINT, iSavepoint);
  return sqlite3Fts5FlushToDisk((Fts5Table*)pVtab);
}