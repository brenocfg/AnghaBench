#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_4__ {int nDb; char** azDb; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ memstat_cursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  memstatClearSchema (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 char** sqlite3_realloc64 (char**,int) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int memstatFindSchemas(memstat_cursor *pCur){
  sqlite3_stmt *pStmt = 0;
  int rc;
  if( pCur->nDb ) return SQLITE_OK;
  rc = sqlite3_prepare_v2(pCur->db, "PRAGMA database_list", -1, &pStmt, 0);
  if( rc ){
    sqlite3_finalize(pStmt);
    return rc;
  }
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    char **az, *z;
    az = sqlite3_realloc64(pCur->azDb, sizeof(char*)*(pCur->nDb+1));
    if( az==0 ){
      memstatClearSchema(pCur);
      return SQLITE_NOMEM;
    }
    pCur->azDb = az;
    z = sqlite3_mprintf("%s", sqlite3_column_text(pStmt, 1));
    if( z==0 ){
      memstatClearSchema(pCur);
      return SQLITE_NOMEM;
    }
    pCur->azDb[pCur->nDb] = z;
    pCur->nDb++;
  }
  sqlite3_finalize(pStmt);
  return SQLITE_OK;
}