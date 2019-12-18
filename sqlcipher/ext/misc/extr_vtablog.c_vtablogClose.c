#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int iInst; } ;
typedef  TYPE_1__ vtablog_vtab ;
struct TYPE_7__ {int iCursor; } ;
typedef  TYPE_2__ vtablog_cursor ;
struct TYPE_8__ {scalar_t__ pVtab; } ;
typedef  TYPE_3__ sqlite3_vtab_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 

__attribute__((used)) static int vtablogClose(sqlite3_vtab_cursor *cur){
  vtablog_cursor *pCur = (vtablog_cursor*)cur;
  vtablog_vtab *pTab = (vtablog_vtab*)cur->pVtab;
  printf("vtablogClose(tab=%d, cursor=%d)\n", pTab->iInst, pCur->iCursor);
  sqlite3_free(cur);
  return SQLITE_OK;
}