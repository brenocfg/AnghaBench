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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  ExpertVtab ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int expertDisconnect(sqlite3_vtab *pVtab){
  ExpertVtab *p = (ExpertVtab*)pVtab;
  sqlite3_free(p);
  return SQLITE_OK;
}