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
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_OPEN_URI ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_open_v2 (char const*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static sqlite3 *openDatabase(const char *zPrg, const char *zName){
  sqlite3 *db = 0;
  int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI;
  int rc = sqlite3_open_v2(zName, &db, flags, 0);
  if( rc!=SQLITE_OK ){
    const char *zErr = sqlite3_errmsg(db);
    fprintf(stderr, "%s: can't open %s (%s)\n", zPrg, zName, zErr);
    sqlite3_close(db);
    exit(1);
  }
  return db;
}