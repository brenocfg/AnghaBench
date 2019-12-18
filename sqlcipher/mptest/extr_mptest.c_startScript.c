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
struct TYPE_2__ {void* iTimeout; int /*<<< orphan*/  db; scalar_t__ nTest; scalar_t__ nError; } ;

/* Variables and functions */
 void* DEFAULT_TIMEOUT ; 
 int SQLITE_BUSY ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  errorMessage (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatalError (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ g ; 
 int /*<<< orphan*/ * prepareSql (char*,int) ; 
 int /*<<< orphan*/  runSql (char*,...) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 char* sqlite3_malloc (int) ; 
 char* sqlite3_mprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_sleep (int) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int trySql (char*) ; 

__attribute__((used)) static int startScript(
  int iClient,              /* The client number */
  char **pzScript,          /* Write task script here */
  int *pTaskId,             /* Write task number here */
  char **pzTaskName         /* Name of the task */
){
  sqlite3_stmt *pStmt = 0;
  int taskId;
  int rc;
  int totalTime = 0;

  *pzScript = 0;
  g.iTimeout = 0;
  while(1){
    rc = trySql("BEGIN IMMEDIATE");
    if( rc==SQLITE_BUSY ){
      sqlite3_sleep(10);
      totalTime += 10;
      continue;
    }
    if( rc!=SQLITE_OK ){
      fatalError("in startScript: %s", sqlite3_errmsg(g.db));
    }
    if( g.nError || g.nTest ){
      runSql("UPDATE counters SET nError=nError+%d, nTest=nTest+%d",
             g.nError, g.nTest);
      g.nError = 0;
      g.nTest = 0;
    }
    pStmt = prepareSql("SELECT 1 FROM client WHERE id=%d AND wantHalt",iClient);
    rc = sqlite3_step(pStmt);
    sqlite3_finalize(pStmt);
    if( rc==SQLITE_ROW ){
      runSql("DELETE FROM client WHERE id=%d", iClient);
      g.iTimeout = DEFAULT_TIMEOUT;
      runSql("COMMIT TRANSACTION;");
      return SQLITE_DONE;
    }
    pStmt = prepareSql(
              "SELECT script, id, name FROM task"
              " WHERE client=%d AND starttime IS NULL"
              " ORDER BY id LIMIT 1", iClient);
    rc = sqlite3_step(pStmt);
    if( rc==SQLITE_ROW ){
      int n = sqlite3_column_bytes(pStmt, 0);
      *pzScript = sqlite3_malloc(n+1);
      strcpy(*pzScript, (const char*)sqlite3_column_text(pStmt, 0));
      *pTaskId = taskId = sqlite3_column_int(pStmt, 1);
      *pzTaskName = sqlite3_mprintf("%s", sqlite3_column_text(pStmt, 2));
      sqlite3_finalize(pStmt);
      runSql("UPDATE task"
             "   SET starttime=strftime('%%Y-%%m-%%d %%H:%%M:%%f','now')"
             " WHERE id=%d;", taskId);
      g.iTimeout = DEFAULT_TIMEOUT;
      runSql("COMMIT TRANSACTION;");
      return SQLITE_OK;
    }
    sqlite3_finalize(pStmt);
    if( rc==SQLITE_DONE ){
      if( totalTime>30000 ){
        errorMessage("Waited over 30 seconds with no work.  Giving up.");
        runSql("DELETE FROM client WHERE id=%d; COMMIT;", iClient);
        sqlite3_close(g.db);
        exit(1);
      }
      while( trySql("COMMIT")==SQLITE_BUSY ){
        sqlite3_sleep(10);
        totalTime += 10;
      }
      sqlite3_sleep(100);
      totalTime += 100;
      continue;
    }
    fatalError("%s", sqlite3_errmsg(g.db));
  }
  g.iTimeout = DEFAULT_TIMEOUT;
}