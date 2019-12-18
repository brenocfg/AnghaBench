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
typedef  int /*<<< orphan*/  fulltext_vtab ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  fulltext_vtab_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fulltextDisconnect(sqlite3_vtab *pVTab){
  TRACE(("FTS2 Disconnect %p\n", pVTab));
  fulltext_vtab_destroy((fulltext_vtab *)pVTab);
  return SQLITE_OK;
}