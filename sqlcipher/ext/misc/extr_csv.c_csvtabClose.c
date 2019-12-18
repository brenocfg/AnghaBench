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
struct TYPE_3__ {int /*<<< orphan*/  rdr; } ;
typedef  TYPE_1__ CsvCursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  csv_reader_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csvtabCursorRowReset (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int csvtabClose(sqlite3_vtab_cursor *cur){
  CsvCursor *pCur = (CsvCursor*)cur;
  csvtabCursorRowReset(pCur);
  csv_reader_reset(&pCur->rdr);
  sqlite3_free(cur);
  return SQLITE_OK;
}