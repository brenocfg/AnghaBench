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
typedef  int /*<<< orphan*/  Fts5Index ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5CloseReader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5IndexDiscardData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5StructureInvalidate (int /*<<< orphan*/ *) ; 

int sqlite3Fts5IndexRollback(Fts5Index *p){
  fts5CloseReader(p);
  fts5IndexDiscardData(p);
  fts5StructureInvalidate(p);
  /* assert( p->rc==SQLITE_OK ); */
  return SQLITE_OK;
}