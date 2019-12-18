#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {char* zDb; int /*<<< orphan*/  zTab; } ;
typedef  TYPE_1__ UnionSrc ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int sqlite3_errcode (int /*<<< orphan*/ *) ; 
 char* sqlite3_mprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_stricmp (char*,char const*) ; 
 int /*<<< orphan*/  sqlite3_table_column_metadata (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unionIsIntkeyTable(
  sqlite3 *db,                    /* Database handle */
  UnionSrc *pSrc,                 /* Source table to test */
  char **pzErr                    /* OUT: Error message */
){
  int bPk = 0;
  const char *zType = 0;
  int rc;

  sqlite3_table_column_metadata(
      db, pSrc->zDb, pSrc->zTab, "_rowid_", &zType, 0, 0, &bPk, 0
  );
  rc = sqlite3_errcode(db);
  if( rc==SQLITE_ERROR 
   || (rc==SQLITE_OK && (!bPk || sqlite3_stricmp("integer", zType)))
  ){
    rc = SQLITE_ERROR;
    *pzErr = sqlite3_mprintf("no such rowid table: %s%s%s",
        (pSrc->zDb ? pSrc->zDb : ""),
        (pSrc->zDb ? "." : ""),
        pSrc->zTab
    );
  }
  return rc;
}