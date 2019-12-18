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
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_2__ {scalar_t__ iRowid; } ;
typedef  TYPE_1__ Fts3tokCursor ;

/* Variables and functions */
 int SQLITE_OK ; 

__attribute__((used)) static int fts3tokRowidMethod(
  sqlite3_vtab_cursor *pCursor,   /* Cursor to retrieve value from */
  sqlite_int64 *pRowid            /* OUT: Rowid value */
){
  Fts3tokCursor *pCsr = (Fts3tokCursor *)pCursor;
  *pRowid = (sqlite3_int64)pCsr->iRowid;
  return SQLITE_OK;
}