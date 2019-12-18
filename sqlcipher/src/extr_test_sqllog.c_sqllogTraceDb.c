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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_2__ {scalar_t__ bConditional; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  SQLITE_IOERR ; 
 int SQLITE_OK ; 
 int SQLLOG_NAMESZ ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,int) ; 
 int sqllogFindAttached (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ sqllogglobal ; 
 int strlen (char*) ; 

__attribute__((used)) static int sqllogTraceDb(sqlite3 *db){
  int bRet = 1;
  if( sqllogglobal.bConditional ){
    char zFile[SQLLOG_NAMESZ];      /* Attached database name */
    int rc = sqllogFindAttached(db, "main", 0, zFile);
    if( rc==SQLITE_OK ){
      int nFile = strlen(zFile);
      if( (SQLLOG_NAMESZ-nFile)<8 ){
        sqlite3_log(SQLITE_IOERR, 
            "sqllogTraceDb(): database name too long (%d bytes)", nFile
        );
        bRet = 0;
      }else{
        memcpy(&zFile[nFile], "-sqllog", 8);
        bRet = !access(zFile, F_OK);
      }
    }
  }
  return bRet;
}