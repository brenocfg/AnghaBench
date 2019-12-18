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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  fsdir_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fsdirResetCursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsdirClose(sqlite3_vtab_cursor *cur){
  fsdir_cursor *pCur = (fsdir_cursor*)cur;

  fsdirResetCursor(pCur);
  sqlite3_free(pCur);
  return SQLITE_OK;
}