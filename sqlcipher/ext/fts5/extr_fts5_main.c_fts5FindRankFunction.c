#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int sqlite3_int64 ;
struct TYPE_14__ {int /*<<< orphan*/  db; } ;
struct TYPE_9__ {scalar_t__ pVtab; } ;
struct TYPE_13__ {char* zRank; char* zRankArgs; int nRankArg; int /*<<< orphan*/ * pRank; int /*<<< orphan*/ * pRankArgStmt; int /*<<< orphan*/ ** apRankArg; TYPE_1__ base; } ;
struct TYPE_10__ {scalar_t__ zErrMsg; } ;
struct TYPE_11__ {TYPE_2__ base; TYPE_6__* pConfig; } ;
struct TYPE_12__ {TYPE_3__ p; } ;
typedef  TYPE_4__ Fts5FullTable ;
typedef  TYPE_5__ Fts5Cursor ;
typedef  TYPE_6__ Fts5Config ;
typedef  int /*<<< orphan*/  Fts5Auxiliary ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_PREPARE_PERSISTENT ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fts5FindAuxiliary (TYPE_4__*,char const*) ; 
 scalar_t__ sqlite3Fts5MallocZero (int*,int) ; 
 char* sqlite3Fts5Mprintf (int*,char*,char const*) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_column_value (int /*<<< orphan*/ *,int) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_mprintf (char*,char const*) ; 
 int sqlite3_prepare_v3 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5FindRankFunction(Fts5Cursor *pCsr){
  Fts5FullTable *pTab = (Fts5FullTable*)(pCsr->base.pVtab);
  Fts5Config *pConfig = pTab->p.pConfig;
  int rc = SQLITE_OK;
  Fts5Auxiliary *pAux = 0;
  const char *zRank = pCsr->zRank;
  const char *zRankArgs = pCsr->zRankArgs;

  if( zRankArgs ){
    char *zSql = sqlite3Fts5Mprintf(&rc, "SELECT %s", zRankArgs);
    if( zSql ){
      sqlite3_stmt *pStmt = 0;
      rc = sqlite3_prepare_v3(pConfig->db, zSql, -1,
                              SQLITE_PREPARE_PERSISTENT, &pStmt, 0);
      sqlite3_free(zSql);
      assert( rc==SQLITE_OK || pCsr->pRankArgStmt==0 );
      if( rc==SQLITE_OK ){
        if( SQLITE_ROW==sqlite3_step(pStmt) ){
          sqlite3_int64 nByte;
          pCsr->nRankArg = sqlite3_column_count(pStmt);
          nByte = sizeof(sqlite3_value*)*pCsr->nRankArg;
          pCsr->apRankArg = (sqlite3_value**)sqlite3Fts5MallocZero(&rc, nByte);
          if( rc==SQLITE_OK ){
            int i;
            for(i=0; i<pCsr->nRankArg; i++){
              pCsr->apRankArg[i] = sqlite3_column_value(pStmt, i);
            }
          }
          pCsr->pRankArgStmt = pStmt;
        }else{
          rc = sqlite3_finalize(pStmt);
          assert( rc!=SQLITE_OK );
        }
      }
    }
  }

  if( rc==SQLITE_OK ){
    pAux = fts5FindAuxiliary(pTab, zRank);
    if( pAux==0 ){
      assert( pTab->p.base.zErrMsg==0 );
      pTab->p.base.zErrMsg = sqlite3_mprintf("no such function: %s", zRank);
      rc = SQLITE_ERROR;
    }
  }

  pCsr->pRank = pAux;
  return rc;
}