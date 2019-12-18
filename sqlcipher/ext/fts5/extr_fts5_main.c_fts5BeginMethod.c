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
typedef  int /*<<< orphan*/  Fts5FullTable ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_BEGIN ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5CheckTransactionState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5NewTransaction (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5BeginMethod(sqlite3_vtab *pVtab){
  fts5CheckTransactionState((Fts5FullTable*)pVtab, FTS5_BEGIN, 0);
  fts5NewTransaction((Fts5FullTable*)pVtab);
  return SQLITE_OK;
}