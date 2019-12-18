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
struct TYPE_3__ {struct TYPE_3__* zStr; } ;
typedef  TYPE_1__ prefixes_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static int prefixesClose(sqlite3_vtab_cursor *cur){
  prefixes_cursor *pCur = (prefixes_cursor*)cur;
  sqlite3_free(pCur->zStr);
  sqlite3_free(pCur);
  return SQLITE_OK;
}