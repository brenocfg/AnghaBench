#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ rc; int /*<<< orphan*/  dbMain; int /*<<< orphan*/  zErrmsg; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_9__ {scalar_t__ eType; int iPkTnum; int /*<<< orphan*/ * azTblType; } ;
typedef  TYPE_2__ RbuObjIter ;

/* Variables and functions */
 scalar_t__ RBU_PK_EXTERNAL ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_TESTCTRL_IMPOSTER ; 
 scalar_t__ prepareAndCollectError (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ prepareFreeAndCollectError (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbuFinalize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* rbuMPrintf (TYPE_1__*,char*,char*,...) ; 
 int /*<<< orphan*/  rbuMPrintfExec (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,char const*) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_test_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void rbuCreateImposterTable2(sqlite3rbu *p, RbuObjIter *pIter){
  if( p->rc==SQLITE_OK && pIter->eType==RBU_PK_EXTERNAL ){
    int tnum = pIter->iPkTnum;    /* Root page of PK index */
    sqlite3_stmt *pQuery = 0;     /* SELECT name ... WHERE rootpage = $tnum */
    const char *zIdx = 0;         /* Name of PK index */
    sqlite3_stmt *pXInfo = 0;     /* PRAGMA main.index_xinfo = $zIdx */
    const char *zComma = "";
    char *zCols = 0;              /* Used to build up list of table cols */
    char *zPk = 0;                /* Used to build up table PK declaration */

    /* Figure out the name of the primary key index for the current table.
    ** This is needed for the argument to "PRAGMA index_xinfo". Set
    ** zIdx to point to a nul-terminated string containing this name. */
    p->rc = prepareAndCollectError(p->dbMain, &pQuery, &p->zErrmsg, 
        "SELECT name FROM sqlite_master WHERE rootpage = ?"
    );
    if( p->rc==SQLITE_OK ){
      sqlite3_bind_int(pQuery, 1, tnum);
      if( SQLITE_ROW==sqlite3_step(pQuery) ){
        zIdx = (const char*)sqlite3_column_text(pQuery, 0);
      }
    }
    if( zIdx ){
      p->rc = prepareFreeAndCollectError(p->dbMain, &pXInfo, &p->zErrmsg,
          sqlite3_mprintf("PRAGMA main.index_xinfo = %Q", zIdx)
      );
    }
    rbuFinalize(p, pQuery);

    while( p->rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pXInfo) ){
      int bKey = sqlite3_column_int(pXInfo, 5);
      if( bKey ){
        int iCid = sqlite3_column_int(pXInfo, 1);
        int bDesc = sqlite3_column_int(pXInfo, 3);
        const char *zCollate = (const char*)sqlite3_column_text(pXInfo, 4);
        zCols = rbuMPrintf(p, "%z%sc%d %s COLLATE %Q", zCols, zComma, 
            iCid, pIter->azTblType[iCid], zCollate
        );
        zPk = rbuMPrintf(p, "%z%sc%d%s", zPk, zComma, iCid, bDesc?" DESC":"");
        zComma = ", ";
      }
    }
    zCols = rbuMPrintf(p, "%z, id INTEGER", zCols);
    rbuFinalize(p, pXInfo);

    sqlite3_test_control(SQLITE_TESTCTRL_IMPOSTER, p->dbMain, "main", 1, tnum);
    rbuMPrintfExec(p, p->dbMain,
        "CREATE TABLE rbu_imposter2(%z, PRIMARY KEY(%z)) WITHOUT ROWID", 
        zCols, zPk
    );
    sqlite3_test_control(SQLITE_TESTCTRL_IMPOSTER, p->dbMain, "main", 0, 0);
  }
}