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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3_value ;

/* Variables and functions */
 int sqlite3Fts3UpdateMethod (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3UpdateMethod(
  sqlite3_vtab *pVtab,            /* Virtual table handle */
  int nArg,                       /* Size of argument array */
  sqlite3_value **apVal,          /* Array of arguments */
  sqlite_int64 *pRowid            /* OUT: The affected (or effected) rowid */
){
  return sqlite3Fts3UpdateMethod(pVtab, nArg, apVal, pRowid);
}