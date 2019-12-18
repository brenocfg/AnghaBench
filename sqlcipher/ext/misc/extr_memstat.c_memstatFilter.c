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
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_3__ {scalar_t__ iDb; scalar_t__ iRowid; } ;
typedef  TYPE_1__ memstat_cursor ;

/* Variables and functions */
 int memstatFindSchemas (TYPE_1__*) ; 
 int memstatNext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int memstatFilter(
  sqlite3_vtab_cursor *pVtabCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  memstat_cursor *pCur = (memstat_cursor *)pVtabCursor;
  int rc = memstatFindSchemas(pCur);
  if( rc ) return rc;
  pCur->iRowid = 0;
  pCur->iDb = 0;
  return memstatNext(pVtabCursor);
}