#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_2__ {scalar_t__ i; } ;
typedef  TYPE_1__ VfsStatCursor ;

/* Variables and functions */
 int SQLITE_OK ; 

__attribute__((used)) static int vstattabFilter(
  sqlite3_vtab_cursor *pVtabCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  VfsStatCursor *pCur = (VfsStatCursor*)pVtabCursor;
  pCur->i = 0;
  return SQLITE_OK;
}