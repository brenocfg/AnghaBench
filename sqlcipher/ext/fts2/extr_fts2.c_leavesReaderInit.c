#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_7__ {int /*<<< orphan*/  nData; int /*<<< orphan*/  pData; } ;
struct TYPE_6__ {int idx; int eof; int /*<<< orphan*/  leafReader; int /*<<< orphan*/ * pStmt; TYPE_3__ rootData; } ;
typedef  TYPE_1__ LeavesReader ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (TYPE_1__*) ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  dataBufferInit (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataBufferReplace (TYPE_3__*,char const*,int) ; 
 int /*<<< orphan*/  leafReaderInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sql_get_leaf_statement (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int leavesReaderInit(fulltext_vtab *v,
                            int idx,
                            sqlite_int64 iStartBlockid,
                            sqlite_int64 iEndBlockid,
                            const char *pRootData, int nRootData,
                            LeavesReader *pReader){
  CLEAR(pReader);
  pReader->idx = idx;

  dataBufferInit(&pReader->rootData, 0);
  if( iStartBlockid==0 ){
    /* Entire leaf level fit in root data. */
    dataBufferReplace(&pReader->rootData, pRootData, nRootData);
    leafReaderInit(pReader->rootData.pData, pReader->rootData.nData,
                   &pReader->leafReader);
  }else{
    sqlite3_stmt *s;
    int rc = sql_get_leaf_statement(v, idx, &s);
    if( rc!=SQLITE_OK ) return rc;

    rc = sqlite3_bind_int64(s, 1, iStartBlockid);
    if( rc!=SQLITE_OK ) return rc;

    rc = sqlite3_bind_int64(s, 2, iEndBlockid);
    if( rc!=SQLITE_OK ) return rc;

    rc = sqlite3_step(s);
    if( rc==SQLITE_DONE ){
      pReader->eof = 1;
      return SQLITE_OK;
    }
    if( rc!=SQLITE_ROW ) return rc;

    pReader->pStmt = s;
    leafReaderInit(sqlite3_column_blob(pReader->pStmt, 0),
                   sqlite3_column_bytes(pReader->pStmt, 0),
                   &pReader->leafReader);
  }
  return SQLITE_OK;
}