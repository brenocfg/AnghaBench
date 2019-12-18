#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
typedef  int /*<<< orphan*/  LeavesReader ;

/* Variables and functions */
 int MERGE_COUNT ; 
 int /*<<< orphan*/  SEGDIR_SELECT_LEVEL_STMT ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  leavesReaderDestroy (int /*<<< orphan*/ *) ; 
 int leavesReaderInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leavesReaderReorder (int /*<<< orphan*/ *,int) ; 
 int sql_get_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 char* sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int leavesReadersInit(fulltext_vtab *v, int iLevel,
                             LeavesReader *pReaders, int *piReaders){
  sqlite3_stmt *s;
  int i, rc = sql_get_statement(v, SEGDIR_SELECT_LEVEL_STMT, &s);
  if( rc!=SQLITE_OK ) return rc;

  rc = sqlite3_bind_int(s, 1, iLevel);
  if( rc!=SQLITE_OK ) return rc;

  i = 0;
  while( (rc = sqlite3_step(s))==SQLITE_ROW ){
    sqlite_int64 iStart = sqlite3_column_int64(s, 0);
    sqlite_int64 iEnd = sqlite3_column_int64(s, 1);
    const char *pRootData = sqlite3_column_blob(s, 2);
    int nRootData = sqlite3_column_bytes(s, 2);

    assert( i<MERGE_COUNT );
    rc = leavesReaderInit(v, i, iStart, iEnd, pRootData, nRootData,
                          &pReaders[i]);
    if( rc!=SQLITE_OK ) break;

    i++;
  }
  if( rc!=SQLITE_DONE ){
    while( i-->0 ){
      leavesReaderDestroy(&pReaders[i]);
    }
    return rc;
  }

  *piReaders = i;

  /* Leave our results sorted by term, then age. */
  while( i-- ){
    leavesReaderReorder(pReaders+i, *piReaders-i);
  }
  return SQLITE_OK;
}