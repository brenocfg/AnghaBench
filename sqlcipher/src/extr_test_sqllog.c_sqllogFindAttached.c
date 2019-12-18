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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_2__ {int bRec; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_log (int,char*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_strnicmp (char const*,char const*,int) ; 
 TYPE_1__ sqllogglobal ; 
 int strlen (char const*) ; 

__attribute__((used)) static int sqllogFindAttached(
  sqlite3 *db,                    /* Database connection */
  const char *zSearch,            /* Name to search for (or NULL) */
  char *zName,                    /* OUT: Name of attached database */
  char *zFile                     /* OUT: Name of attached file */
){
  sqlite3_stmt *pStmt;
  int rc;

  /* The "PRAGMA database_list" command returns a list of databases in the
  ** order that they were attached. So a newly attached database is 
  ** described by the last row returned.  */
  assert( sqllogglobal.bRec==0 );
  sqllogglobal.bRec = 1;
  rc = sqlite3_prepare_v2(db, "PRAGMA database_list", -1, &pStmt, 0);
  if( rc==SQLITE_OK ){
    while( SQLITE_ROW==sqlite3_step(pStmt) ){
      const char *zVal1; int nVal1;
      const char *zVal2; int nVal2;

      zVal1 = (const char*)sqlite3_column_text(pStmt, 1);
      nVal1 = sqlite3_column_bytes(pStmt, 1);
      if( zName ){
        memcpy(zName, zVal1, nVal1+1);
      }

      zVal2 = (const char*)sqlite3_column_text(pStmt, 2);
      nVal2 = sqlite3_column_bytes(pStmt, 2);
      memcpy(zFile, zVal2, nVal2+1);

      if( zSearch && strlen(zSearch)==nVal1 
       && 0==sqlite3_strnicmp(zSearch, zVal1, nVal1)
      ){
        break;
      }
    }
    rc = sqlite3_finalize(pStmt);
  }
  sqllogglobal.bRec = 0;

  if( rc!=SQLITE_OK ){
    sqlite3_log(rc, "sqllogFindAttached(): error in \"PRAGMA database_list\"");
  }
  return rc;
}