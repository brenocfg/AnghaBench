#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int iInst; } ;
typedef  TYPE_1__ vtablog_vtab ;
struct TYPE_6__ {int iCursor; scalar_t__ iRowid; } ;
typedef  TYPE_2__ vtablog_cursor ;
struct TYPE_7__ {scalar_t__ pVtab; } ;
typedef  TYPE_3__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int vtablogFilter(
  sqlite3_vtab_cursor *cur,
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  vtablog_cursor *pCur = (vtablog_cursor *)cur;
  vtablog_vtab *pTab = (vtablog_vtab*)cur->pVtab;
  printf("vtablogFilter(tab=%d, cursor=%d):\n", pTab->iInst, pCur->iCursor);
  pCur->iRowid = 0;
  return SQLITE_OK;
}