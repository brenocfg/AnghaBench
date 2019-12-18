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
struct TYPE_8__ {int rc; int /*<<< orphan*/  zErrmsg; int /*<<< orphan*/  dbMain; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_9__ {char const* zIdx; int bCleanup; char const* zTbl; char const* zDataTbl; int /*<<< orphan*/ * pIdxIter; void* bUnique; void* iTnum; int /*<<< orphan*/ * pTblIter; } ;
typedef  TYPE_2__ RbuObjIter ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  rbuObjIterClearStatements (TYPE_2__*) ; 
 int /*<<< orphan*/  rbuObjIterFinalize (TYPE_2__*) ; 
 int /*<<< orphan*/  rbuObjIterFreeCols (TYPE_2__*) ; 
 int resetAndCollectError (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 void* sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rbuObjIterNext(sqlite3rbu *p, RbuObjIter *pIter){
  int rc = p->rc;
  if( rc==SQLITE_OK ){

    /* Free any SQLite statements used while processing the previous object */ 
    rbuObjIterClearStatements(pIter);
    if( pIter->zIdx==0 ){
      rc = sqlite3_exec(p->dbMain,
          "DROP TRIGGER IF EXISTS temp.rbu_insert_tr;"
          "DROP TRIGGER IF EXISTS temp.rbu_update1_tr;"
          "DROP TRIGGER IF EXISTS temp.rbu_update2_tr;"
          "DROP TRIGGER IF EXISTS temp.rbu_delete_tr;"
          , 0, 0, &p->zErrmsg
      );
    }

    if( rc==SQLITE_OK ){
      if( pIter->bCleanup ){
        rbuObjIterFreeCols(pIter);
        pIter->bCleanup = 0;
        rc = sqlite3_step(pIter->pTblIter);
        if( rc!=SQLITE_ROW ){
          rc = resetAndCollectError(pIter->pTblIter, &p->zErrmsg);
          pIter->zTbl = 0;
        }else{
          pIter->zTbl = (const char*)sqlite3_column_text(pIter->pTblIter, 0);
          pIter->zDataTbl = (const char*)sqlite3_column_text(pIter->pTblIter,1);
          rc = (pIter->zDataTbl && pIter->zTbl) ? SQLITE_OK : SQLITE_NOMEM;
        }
      }else{
        if( pIter->zIdx==0 ){
          sqlite3_stmt *pIdx = pIter->pIdxIter;
          rc = sqlite3_bind_text(pIdx, 1, pIter->zTbl, -1, SQLITE_STATIC);
        }
        if( rc==SQLITE_OK ){
          rc = sqlite3_step(pIter->pIdxIter);
          if( rc!=SQLITE_ROW ){
            rc = resetAndCollectError(pIter->pIdxIter, &p->zErrmsg);
            pIter->bCleanup = 1;
            pIter->zIdx = 0;
          }else{
            pIter->zIdx = (const char*)sqlite3_column_text(pIter->pIdxIter, 0);
            pIter->iTnum = sqlite3_column_int(pIter->pIdxIter, 1);
            pIter->bUnique = sqlite3_column_int(pIter->pIdxIter, 2);
            rc = pIter->zIdx ? SQLITE_OK : SQLITE_NOMEM;
          }
        }
      }
    }
  }

  if( rc!=SQLITE_OK ){
    rbuObjIterFinalize(pIter);
    p->rc = rc;
  }
  return rc;
}