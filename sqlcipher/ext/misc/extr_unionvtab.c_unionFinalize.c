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
 int SQLITE_OK ; 
 int /*<<< orphan*/ * sqlite3_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unionFinalize(int *pRc, sqlite3_stmt *pStmt, char **pzErr){
  sqlite3 *db = sqlite3_db_handle(pStmt);
  int rc = sqlite3_finalize(pStmt);
  if( *pRc==SQLITE_OK ){
    *pRc = rc;
    if( rc ){
      *pzErr = sqlite3_mprintf("%s", sqlite3_errmsg(db));
    }
  }
}