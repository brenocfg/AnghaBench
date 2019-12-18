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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
typedef  int /*<<< orphan*/  fulltext_statement ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int sql_step_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int sql_single_step_statement(fulltext_vtab *v,
                                     fulltext_statement iStmt,
                                     sqlite3_stmt **ppStmt){
  int rc = sql_step_statement(v, iStmt, ppStmt);
  return (rc==SQLITE_DONE) ? SQLITE_OK : rc;
}