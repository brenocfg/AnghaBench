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
 int /*<<< orphan*/  TRACE (char*) ; 
 int flushPendingTerms (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fulltextSync(sqlite3_vtab *pVtab){
  TRACE(("FTS2 xSync()\n"));
  return flushPendingTerms((fulltext_vtab *)pVtab);
}