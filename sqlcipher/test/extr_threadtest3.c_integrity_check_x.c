#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_7__ {int rc; char* zErr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pStmt; } ;
typedef  TYPE_1__ Statement ;
typedef  int /*<<< orphan*/  Sqlite ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 TYPE_1__* getSqlStatement (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* sqlite3_mprintf (char*,char const*,...) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void integrity_check_x(
  Error *pErr,                    /* IN/OUT: Error code */
  Sqlite *pDb                     /* Database handle */
){
  if( pErr->rc==SQLITE_OK ){
    Statement *pStatement;        /* Statement to execute */
    char *zErr = 0;               /* Integrity check error */

    pStatement = getSqlStatement(pErr, pDb, "PRAGMA integrity_check");
    if( pStatement ){
      sqlite3_stmt *pStmt = pStatement->pStmt;
      while( SQLITE_ROW==sqlite3_step(pStmt) ){
        const char *z = (const char*)sqlite3_column_text(pStmt, 0);
        if( strcmp(z, "ok") ){
          if( zErr==0 ){
            zErr = sqlite3_mprintf("%s", z);
          }else{
            zErr = sqlite3_mprintf("%z\n%s", zErr, z);
          }
        }
      }
      sqlite3_reset(pStmt);

      if( zErr ){
        pErr->zErr = zErr;
        pErr->rc = 1;
      }
    }
  }
}