#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_11__ {scalar_t__ nPendingData; int nColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;
struct TYPE_12__ {scalar_t__ nData; int /*<<< orphan*/  pData; } ;
typedef  int /*<<< orphan*/  DocListType ;
typedef  TYPE_2__ DataBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DEFAULT ; 
 int /*<<< orphan*/  SEGDIR_SELECT_ALL_STMT ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dataBufferDestroy (TYPE_2__*) ; 
 int /*<<< orphan*/  dataBufferInit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  docListTrim (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int loadSegment (TYPE_1__*,char const*,int const,int /*<<< orphan*/  const,char const*,int,int,TYPE_2__*) ; 
 int sql_get_statement (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 char* sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int termSelect(fulltext_vtab *v, int iColumn,
                      const char *pTerm, int nTerm, int isPrefix,
                      DocListType iType, DataBuffer *out){
  DataBuffer doclist;
  sqlite3_stmt *s;
  int rc = sql_get_statement(v, SEGDIR_SELECT_ALL_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  /* This code should never be called with buffered updates. */
  assert( v->nPendingData<0 );

  dataBufferInit(&doclist, 0);

  /* Traverse the segments from oldest to newest so that newer doclist
  ** elements for given docids overwrite older elements.
  */
  while( (rc = sqlite3_step(s))==SQLITE_ROW ){
    const char *pData = sqlite3_column_blob(s, 2);
    const int nData = sqlite3_column_bytes(s, 2);
    const sqlite_int64 iLeavesEnd = sqlite3_column_int64(s, 1);
    rc = loadSegment(v, pData, nData, iLeavesEnd, pTerm, nTerm, isPrefix,
                     &doclist);
    if( rc!=SQLITE_OK ) goto err;
  }
  if( rc==SQLITE_DONE ){
    if( doclist.nData!=0 ){
      /* TODO(shess) The old term_select_all() code applied the column
      ** restrict as we merged segments, leading to smaller buffers.
      ** This is probably worthwhile to bring back, once the new storage
      ** system is checked in.
      */
      if( iColumn==v->nColumn) iColumn = -1;
      docListTrim(DL_DEFAULT, doclist.pData, doclist.nData,
                  iColumn, iType, out);
    }
    rc = SQLITE_OK;
  }

 err:
  dataBufferDestroy(&doclist);
  return rc;
}