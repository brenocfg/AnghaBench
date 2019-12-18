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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_open (char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static sqlite3 *openDb(const char *zFilename){
  int rc;
  sqlite3 *db;
  rc = sqlite3_open(zFilename, &db);
  if( rc ){
    fprintf(stderr, "Cannot open \"%s\": %s\n",
            zFilename, sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
  return db;
}