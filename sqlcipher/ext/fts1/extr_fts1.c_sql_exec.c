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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* string_format (char const*,char const*,char const*) ; 

__attribute__((used)) static int sql_exec(sqlite3 *db, const char *zDb, const char *zName,
                    const char *zFormat){
  char *zCommand = string_format(zFormat, zDb, zName);
  int rc;
  TRACE(("FTS1 sql: %s\n", zCommand));
  rc = sqlite3_exec(db, zCommand, NULL, 0, NULL);
  free(zCommand);
  return rc;
}