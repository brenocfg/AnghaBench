#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  startupInfo ;
typedef  int /*<<< orphan*/  processInfo ;
struct TYPE_8__ {int iTrace; scalar_t__ zVfs; scalar_t__ bSync; scalar_t__ bSqlTrace; int /*<<< orphan*/  zDbFile; int /*<<< orphan*/  argv0; int /*<<< orphan*/  db; } ;
struct TYPE_7__ {int cb; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_1__ PROCESS_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  errorMessage (char*,int) ; 
 TYPE_4__ g ; 
 int /*<<< orphan*/  logMessage (char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  runSql (char*,int) ; 
 scalar_t__ sqlite3_changes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char*,...) ; 
 int system (char*) ; 

__attribute__((used)) static void startClient(int iClient){
  runSql("INSERT OR IGNORE INTO client VALUES(%d,0)", iClient);
  if( sqlite3_changes(g.db) ){
    char *zSys;
    int rc;
    zSys = sqlite3_mprintf("%s \"%s\" --client %d --trace %d",
                 g.argv0, g.zDbFile, iClient, g.iTrace);
    if( g.bSqlTrace ){
      zSys = sqlite3_mprintf("%z --sqltrace", zSys);
    }
    if( g.bSync ){
      zSys = sqlite3_mprintf("%z --sync", zSys);
    }
    if( g.zVfs ){
      zSys = sqlite3_mprintf("%z --vfs \"%s\"", zSys, g.zVfs);
    }
    if( g.iTrace>=2 ) logMessage("system('%q')", zSys);
#if !defined(_WIN32)
    zSys = sqlite3_mprintf("%z &", zSys);
    rc = system(zSys);
    if( rc ) errorMessage("system() fails with error code %d", rc);
#else
    {
      STARTUPINFOA startupInfo;
      PROCESS_INFORMATION processInfo;
      memset(&startupInfo, 0, sizeof(startupInfo));
      startupInfo.cb = sizeof(startupInfo);
      memset(&processInfo, 0, sizeof(processInfo));
      rc = CreateProcessA(NULL, zSys, NULL, NULL, FALSE, 0, NULL, NULL,
                        &startupInfo, &processInfo);
      if( rc ){
        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);
      }else{
        errorMessage("CreateProcessA() fails with error code %lu",
                     GetLastError());
      }
    }
#endif
    sqlite3_free(zSys);
  }
}