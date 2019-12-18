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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int sqlite3_prepare (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* string_format (char const*,char const*,char const*) ; 

__attribute__((used)) static int sql_prepare(sqlite3 *db, const char *zDb, const char *zName,
                       sqlite3_stmt **ppStmt, const char *zFormat){
  char *zCommand = string_format(zFormat, zDb, zName);
  int rc;
  TRACE(("FTS1 prepare: %s\n", zCommand));
  rc = sqlite3_prepare(db, zCommand, -1, ppStmt, NULL);
  free(zCommand);
  return rc;
}