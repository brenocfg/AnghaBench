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

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int echoRollbackTo(sqlite3_vtab *pVTab, int iSavepoint){
  assert( pVTab );
  return SQLITE_OK;
}