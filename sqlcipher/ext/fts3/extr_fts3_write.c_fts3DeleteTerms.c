#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_7__ {int nColumn; scalar_t__* abNotindexed; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQL_SELECT_CONTENT_BY_ROWID ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3PendingTermsAdd (TYPE_1__*,int,char const*,int,int /*<<< orphan*/ *) ; 
 int fts3PendingTermsDocid (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int fts3SqlStmt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int langidFromSelect (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts3DeleteTerms( 
  int *pRC,               /* Result code */
  Fts3Table *p,           /* The FTS table to delete from */
  sqlite3_value *pRowid,  /* The docid to be deleted */
  u32 *aSz,               /* Sizes of deleted document written here */
  int *pbFound            /* OUT: Set to true if row really does exist */
){
  int rc;
  sqlite3_stmt *pSelect;

  assert( *pbFound==0 );
  if( *pRC ) return;
  rc = fts3SqlStmt(p, SQL_SELECT_CONTENT_BY_ROWID, &pSelect, &pRowid);
  if( rc==SQLITE_OK ){
    if( SQLITE_ROW==sqlite3_step(pSelect) ){
      int i;
      int iLangid = langidFromSelect(p, pSelect);
      i64 iDocid = sqlite3_column_int64(pSelect, 0);
      rc = fts3PendingTermsDocid(p, 1, iLangid, iDocid);
      for(i=1; rc==SQLITE_OK && i<=p->nColumn; i++){
        int iCol = i-1;
        if( p->abNotindexed[iCol]==0 ){
          const char *zText = (const char *)sqlite3_column_text(pSelect, i);
          rc = fts3PendingTermsAdd(p, iLangid, zText, -1, &aSz[iCol]);
          aSz[p->nColumn] += sqlite3_column_bytes(pSelect, i);
        }
      }
      if( rc!=SQLITE_OK ){
        sqlite3_reset(pSelect);
        *pRC = rc;
        return;
      }
      *pbFound = 1;
    }
    rc = sqlite3_reset(pSelect);
  }else{
    sqlite3_reset(pSelect);
  }
  *pRC = rc;
}