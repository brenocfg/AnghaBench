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
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  checkfreelist_function ; 
 int /*<<< orphan*/  readint_function ; 
 int sqlite3_create_function (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cflRegister(sqlite3 *db){
  int rc = sqlite3_create_function(
      db, "sqlite_readint32", -1, SQLITE_UTF8, 0, readint_function, 0, 0
  );
  if( rc!=SQLITE_OK ) return rc;
  rc = sqlite3_create_function(
      db, "checkfreelist", 1, SQLITE_UTF8, 0, checkfreelist_function, 0, 0
  );
  return rc;
}