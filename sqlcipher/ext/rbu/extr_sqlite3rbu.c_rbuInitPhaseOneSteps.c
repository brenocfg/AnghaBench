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
struct TYPE_3__ {scalar_t__ rc; int nPhaseOneStep; int /*<<< orphan*/  zErrmsg; int /*<<< orphan*/  dbRbu; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 void* prepareAndCollectError (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rbuIndexCntFunc ; 
 int sqlite3_column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_create_function (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbuInitPhaseOneSteps(sqlite3rbu *p){
  if( p->rc==SQLITE_OK ){
    sqlite3_stmt *pStmt = 0;
    int bExists = 0;                /* True if rbu_count exists */

    p->nPhaseOneStep = -1;

    p->rc = sqlite3_create_function(p->dbRbu, 
        "rbu_index_cnt", 1, SQLITE_UTF8, (void*)p, rbuIndexCntFunc, 0, 0
    );
  
    /* Check for the rbu_count table. If it does not exist, or if an error
    ** occurs, nPhaseOneStep will be left set to -1. */
    if( p->rc==SQLITE_OK ){
      p->rc = prepareAndCollectError(p->dbRbu, &pStmt, &p->zErrmsg,
          "SELECT 1 FROM sqlite_master WHERE tbl_name = 'rbu_count'"
      );
    }
    if( p->rc==SQLITE_OK ){
      if( SQLITE_ROW==sqlite3_step(pStmt) ){
        bExists = 1;
      }
      p->rc = sqlite3_finalize(pStmt);
    }
  
    if( p->rc==SQLITE_OK && bExists ){
      p->rc = prepareAndCollectError(p->dbRbu, &pStmt, &p->zErrmsg,
          "SELECT sum(cnt * (1 + rbu_index_cnt(rbu_target_name(tbl))))"
          "FROM rbu_count"
      );
      if( p->rc==SQLITE_OK ){
        if( SQLITE_ROW==sqlite3_step(pStmt) ){
          p->nPhaseOneStep = sqlite3_column_int64(pStmt, 0);
        }
        p->rc = sqlite3_finalize(pStmt);
      }
    }
  }
}