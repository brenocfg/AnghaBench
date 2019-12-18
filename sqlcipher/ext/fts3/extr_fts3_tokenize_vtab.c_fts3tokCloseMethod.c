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
typedef  int /*<<< orphan*/  Fts3tokCursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts3tokResetCursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3tokCloseMethod(sqlite3_vtab_cursor *pCursor){
  Fts3tokCursor *pCsr = (Fts3tokCursor *)pCursor;

  fts3tokResetCursor(pCsr);
  sqlite3_free(pCsr);
  return SQLITE_OK;
}