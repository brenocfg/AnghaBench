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
struct TYPE_2__ {int iRowid; scalar_t__ iDb; } ;
typedef  TYPE_1__ memstat_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 

__attribute__((used)) static int memstatRowid(sqlite3_vtab_cursor *cur, sqlite_int64 *pRowid){
  memstat_cursor *pCur = (memstat_cursor*)cur;
  *pRowid = pCur->iRowid*1000 + pCur->iDb;
  return SQLITE_OK;
}