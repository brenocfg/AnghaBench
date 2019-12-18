#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ rc; int /*<<< orphan*/  dbMain; int /*<<< orphan*/  zErrmsg; int /*<<< orphan*/  dbRbu; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 scalar_t__ prepareFreeAndCollectError (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbuFinalize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ rbuMPrintfExec (TYPE_1__*,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,char const*) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbuCopyPragma(sqlite3rbu *p, const char *zPragma){
  if( p->rc==SQLITE_OK ){
    sqlite3_stmt *pPragma = 0;
    p->rc = prepareFreeAndCollectError(p->dbRbu, &pPragma, &p->zErrmsg, 
        sqlite3_mprintf("PRAGMA main.%s", zPragma)
    );
    if( p->rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pPragma) ){
      p->rc = rbuMPrintfExec(p, p->dbMain, "PRAGMA main.%s = %d",
          zPragma, sqlite3_column_int(pPragma, 0)
      );
    }
    rbuFinalize(p, pPragma);
  }
}