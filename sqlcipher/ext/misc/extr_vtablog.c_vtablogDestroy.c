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
struct TYPE_2__ {int iInst; } ;
typedef  TYPE_1__ vtablog_vtab ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vtablogDestroy(sqlite3_vtab *pVtab){
  vtablog_vtab *pTab = (vtablog_vtab*)pVtab;
  printf("vtablogDestroy(%d)\n", pTab->iInst);
  sqlite3_free(pVtab);
  return SQLITE_OK;
}