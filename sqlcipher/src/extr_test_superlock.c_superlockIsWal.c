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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {int bWal; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Superlock ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_strnicmp (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int superlockIsWal(Superlock *pLock){
  int rc;                         /* Return Code */
  sqlite3_stmt *pStmt;            /* Compiled PRAGMA journal_mode statement */

  rc = sqlite3_prepare(pLock->db, "PRAGMA main.journal_mode", -1, &pStmt, 0);
  if( rc!=SQLITE_OK ) return rc;

  pLock->bWal = 0;
  if( SQLITE_ROW==sqlite3_step(pStmt) ){
    const char *zMode = (const char *)sqlite3_column_text(pStmt, 0);
    if( zMode && strlen(zMode)==3 && sqlite3_strnicmp("wal", zMode, 3)==0 ){
      pLock->bWal = 1;
    }
  }

  return sqlite3_finalize(pStmt);
}