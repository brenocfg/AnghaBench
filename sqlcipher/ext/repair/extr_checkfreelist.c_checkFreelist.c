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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int checkFreelistError (char**,char*,int,...) ; 
 int get4byte (int /*<<< orphan*/  const*) ; 
 int sqlGetInteger (int /*<<< orphan*/ *,char const*,char*,int*) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int checkFreelist(
  sqlite3 *db, 
  const char *zDb,
  char **pzOut
){
  /* This query returns one row for each page on the free list. Each row has
  ** two columns - the page number and page content.  */
  const char *zTrunk = 
    "WITH freelist_trunk(i, d, n) AS ("
      "SELECT 1, NULL, sqlite_readint32(data, 32) "
      "FROM sqlite_dbpage(:1) WHERE pgno=1 "
        "UNION ALL "
      "SELECT n, data, sqlite_readint32(data) "
      "FROM freelist_trunk, sqlite_dbpage(:1) WHERE pgno=n "
    ")"
    "SELECT i, d FROM freelist_trunk WHERE i!=1;";

  int rc, rc2;                    /* Return code */
  sqlite3_stmt *pTrunk = 0;       /* Compilation of zTrunk */
  u32 nPage = 0;                  /* Number of pages in db */
  u32 nExpected = 0;              /* Expected number of free pages */
  u32 nFree = 0;                  /* Number of pages on free list */

  if( zDb==0 ) zDb = "main";

  if( (rc = sqlGetInteger(db, zDb, "PRAGMA %s.page_count", &nPage))
   || (rc = sqlGetInteger(db, zDb, "PRAGMA %s.freelist_count", &nExpected))
  ){
    return rc;
  }

  rc = sqlite3_prepare_v2(db, zTrunk, -1, &pTrunk, 0);
  if( rc!=SQLITE_OK ) return rc;
  sqlite3_bind_text(pTrunk, 1, zDb, -1, SQLITE_STATIC);
  while( rc==SQLITE_OK && sqlite3_step(pTrunk)==SQLITE_ROW ){
    u32 i;
    u32 iTrunk = (u32)sqlite3_column_int(pTrunk, 0);
    const u8 *aData = (const u8*)sqlite3_column_blob(pTrunk, 1);
    u32 nData = (u32)sqlite3_column_bytes(pTrunk, 1);
    u32 iNext = get4byte(&aData[0]);
    u32 nLeaf = get4byte(&aData[4]);

    if( nLeaf>((nData/4)-2-6) ){
      rc = checkFreelistError(pzOut, 
          "leaf count out of range (%d) on trunk page %d", 
          (int)nLeaf, (int)iTrunk
      );
      nLeaf = (nData/4) - 2 - 6;
    }

    nFree += 1+nLeaf;
    if( iNext>nPage ){
      rc = checkFreelistError(pzOut, 
          "trunk page %d is out of range", (int)iNext
      );
    }

    for(i=0; rc==SQLITE_OK && i<nLeaf; i++){
      u32 iLeaf = get4byte(&aData[8 + 4*i]);
      if( iLeaf==0 || iLeaf>nPage ){
        rc = checkFreelistError(pzOut,
            "leaf page %d is out of range (child %d of trunk page %d)", 
            (int)iLeaf, (int)i, (int)iTrunk
        );
      }
    }
  }

  if( rc==SQLITE_OK && nFree!=nExpected ){
    rc = checkFreelistError(pzOut,
        "free-list count mismatch: actual=%d header=%d", 
        (int)nFree, (int)nExpected
    );
  }

  rc2 = sqlite3_finalize(pTrunk);
  if( rc==SQLITE_OK ) rc = rc2;
  return rc;
}