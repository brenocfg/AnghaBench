#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_2__ {scalar_t__ iTimeout; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_TIMEOUT ; 
 int SQLITE_BUSY ; 
 int SQLITE_DONE ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  errorMessage (char*,char*,...) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/ * prepareSql (char*,...) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_sleep (int) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void waitForClient(int iClient, int iTimeout, char *zErrPrefix){
  sqlite3_stmt *pStmt;
  int rc;
  if( iClient>0 ){
    pStmt = prepareSql(
               "SELECT 1 FROM task"
               " WHERE client=%d"
               "   AND client IN (SELECT id FROM client)"
               "  AND endtime IS NULL",
               iClient);
  }else{
    pStmt = prepareSql(
               "SELECT 1 FROM task"
               " WHERE client IN (SELECT id FROM client)"
               "   AND endtime IS NULL");
  }
  g.iTimeout = 0;
  while( ((rc = sqlite3_step(pStmt))==SQLITE_BUSY || rc==SQLITE_ROW)
    && iTimeout>0
  ){
    sqlite3_reset(pStmt);
    sqlite3_sleep(50);
    iTimeout -= 50;
  }
  sqlite3_finalize(pStmt);
  g.iTimeout = DEFAULT_TIMEOUT;
  if( rc!=SQLITE_DONE ){
    if( zErrPrefix==0 ) zErrPrefix = "";
    if( iClient>0 ){
      errorMessage("%stimeout waiting for client %d", zErrPrefix, iClient);
    }else{
      errorMessage("%stimeout waiting for all clients", zErrPrefix);
    }
  }
}