#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_10__ {scalar_t__ nSegment; } ;
struct TYPE_9__ {scalar_t__ aIndex; } ;
typedef  TYPE_1__ Fts3Table ;
typedef  int /*<<< orphan*/  Fts3SegReader ;
typedef  TYPE_2__ Fts3MultiSegReader ;

/* Variables and functions */
 int FTS3_SEGCURSOR_PENDING ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int fts3SegReaderCursorAppend (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int fts3SelectLeaf (TYPE_1__*,char const*,int,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqlite3Fts3AllSegdirs (TYPE_1__*,int,int,int,int /*<<< orphan*/ **) ; 
 int sqlite3Fts3SegReaderNew (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **) ; 
 int sqlite3Fts3SegReaderPending (TYPE_1__*,int,char const*,int,int,int /*<<< orphan*/ **) ; 
 char* sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3SegReaderCursor(
  Fts3Table *p,                   /* FTS3 table handle */
  int iLangid,                    /* Language id */
  int iIndex,                     /* Index to search (from 0 to p->nIndex-1) */
  int iLevel,                     /* Level of segments to scan */
  const char *zTerm,              /* Term to query for */
  int nTerm,                      /* Size of zTerm in bytes */
  int isPrefix,                   /* True for a prefix search */
  int isScan,                     /* True to scan from zTerm to EOF */
  Fts3MultiSegReader *pCsr        /* Cursor object to populate */
){
  int rc = SQLITE_OK;             /* Error code */
  sqlite3_stmt *pStmt = 0;        /* Statement to iterate through segments */
  int rc2;                        /* Result of sqlite3_reset() */

  /* If iLevel is less than 0 and this is not a scan, include a seg-reader 
  ** for the pending-terms. If this is a scan, then this call must be being
  ** made by an fts4aux module, not an FTS table. In this case calling
  ** Fts3SegReaderPending might segfault, as the data structures used by 
  ** fts4aux are not completely populated. So it's easiest to filter these
  ** calls out here.  */
  if( iLevel<0 && p->aIndex ){
    Fts3SegReader *pSeg = 0;
    rc = sqlite3Fts3SegReaderPending(p, iIndex, zTerm, nTerm, isPrefix||isScan, &pSeg);
    if( rc==SQLITE_OK && pSeg ){
      rc = fts3SegReaderCursorAppend(pCsr, pSeg);
    }
  }

  if( iLevel!=FTS3_SEGCURSOR_PENDING ){
    if( rc==SQLITE_OK ){
      rc = sqlite3Fts3AllSegdirs(p, iLangid, iIndex, iLevel, &pStmt);
    }

    while( rc==SQLITE_OK && SQLITE_ROW==(rc = sqlite3_step(pStmt)) ){
      Fts3SegReader *pSeg = 0;

      /* Read the values returned by the SELECT into local variables. */
      sqlite3_int64 iStartBlock = sqlite3_column_int64(pStmt, 1);
      sqlite3_int64 iLeavesEndBlock = sqlite3_column_int64(pStmt, 2);
      sqlite3_int64 iEndBlock = sqlite3_column_int64(pStmt, 3);
      int nRoot = sqlite3_column_bytes(pStmt, 4);
      char const *zRoot = sqlite3_column_blob(pStmt, 4);

      /* If zTerm is not NULL, and this segment is not stored entirely on its
      ** root node, the range of leaves scanned can be reduced. Do this. */
      if( iStartBlock && zTerm && zRoot ){
        sqlite3_int64 *pi = (isPrefix ? &iLeavesEndBlock : 0);
        rc = fts3SelectLeaf(p, zTerm, nTerm, zRoot, nRoot, &iStartBlock, pi);
        if( rc!=SQLITE_OK ) goto finished;
        if( isPrefix==0 && isScan==0 ) iLeavesEndBlock = iStartBlock;
      }
 
      rc = sqlite3Fts3SegReaderNew(pCsr->nSegment+1, 
          (isPrefix==0 && isScan==0),
          iStartBlock, iLeavesEndBlock, 
          iEndBlock, zRoot, nRoot, &pSeg
      );
      if( rc!=SQLITE_OK ) goto finished;
      rc = fts3SegReaderCursorAppend(pCsr, pSeg);
    }
  }

 finished:
  rc2 = sqlite3_reset(pStmt);
  if( rc==SQLITE_DONE ) rc = rc2;

  return rc;
}