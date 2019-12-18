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

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sql_single_step(sqlite3_stmt *s){
  int rc = sqlite3_step(s);
  return (rc==SQLITE_DONE) ? SQLITE_OK : rc;
}