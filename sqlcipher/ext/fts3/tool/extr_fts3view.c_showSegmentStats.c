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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/ * prepare (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 double sqlite3_column_double (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void showSegmentStats(sqlite3 *db, const char *zTab){
  sqlite3_stmt *pStmt;
  int nSeg = 0;
  sqlite3_int64 szSeg = 0, mxSeg = 0;
  int nIdx = 0;
  sqlite3_int64 szIdx = 0, mxIdx = 0;
  int nRoot = 0;
  sqlite3_int64 szRoot = 0, mxRoot = 0;
  sqlite3_int64 mx;
  int nLeaf;
  int n;
  int pgsz;
  int mxLevel;
  int i;

  pStmt = prepare(db,
                  "SELECT count(*), sum(length(block)), max(length(block))"
                  " FROM '%q_segments'",
                  zTab);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    nSeg = sqlite3_column_int(pStmt, 0);
    szSeg = sqlite3_column_int64(pStmt, 1);
    mxSeg = sqlite3_column_int64(pStmt, 2);
  }
  sqlite3_finalize(pStmt);
  pStmt = prepare(db,
            "SELECT count(*), sum(length(block)), max(length(block))"
            "  FROM '%q_segments' a JOIN '%q_segdir' b"
            " WHERE a.blockid BETWEEN b.leaves_end_block+1 AND b.end_block",
            zTab, zTab);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    nIdx = sqlite3_column_int(pStmt, 0);
    szIdx = sqlite3_column_int64(pStmt, 1);
    mxIdx = sqlite3_column_int64(pStmt, 2);
  }
  sqlite3_finalize(pStmt);
  pStmt = prepare(db,
            "SELECT count(*), sum(length(root)), max(length(root))"
            "  FROM '%q_segdir'",
            zTab);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    nRoot = sqlite3_column_int(pStmt, 0);
    szRoot = sqlite3_column_int64(pStmt, 1);
    mxRoot = sqlite3_column_int64(pStmt, 2);
  }
  sqlite3_finalize(pStmt);

  printf("Number of segments....................... %9d\n", nSeg+nRoot);
  printf("Number of leaf segments.................. %9d\n", nSeg-nIdx);
  printf("Number of index segments................. %9d\n", nIdx);
  printf("Number of root segments.................. %9d\n", nRoot);
  printf("Total size of all segments............... %9lld\n", szSeg+szRoot);
  printf("Total size of all leaf segments.......... %9lld\n", szSeg-szIdx);
  printf("Total size of all index segments......... %9lld\n", szIdx);
  printf("Total size of all root segments.......... %9lld\n", szRoot);
  if( nSeg>0 ){
    printf("Average size of all segments............. %11.1f\n",
            (double)(szSeg+szRoot)/(double)(nSeg+nRoot));
    printf("Average size of leaf segments............ %11.1f\n",
            (double)(szSeg-szIdx)/(double)(nSeg-nIdx));
  }
  if( nIdx>0 ){
    printf("Average size of index segments........... %11.1f\n",
            (double)szIdx/(double)nIdx);
  }
  if( nRoot>0 ){
    printf("Average size of root segments............ %11.1f\n",
            (double)szRoot/(double)nRoot);
  }
  mx = mxSeg;
  if( mx<mxRoot ) mx = mxRoot;
  printf("Maximum segment size..................... %9lld\n", mx);
  printf("Maximum index segment size............... %9lld\n", mxIdx);
  printf("Maximum root segment size................ %9lld\n", mxRoot);

  pStmt = prepare(db, "PRAGMA page_size");
  pgsz = 1024;
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    pgsz = sqlite3_column_int(pStmt, 0);
  }
  sqlite3_finalize(pStmt);
  printf("Database page size....................... %9d\n", pgsz);
  pStmt = prepare(db,
            "SELECT count(*)"
            "  FROM '%q_segments' a JOIN '%q_segdir' b"
            " WHERE a.blockid BETWEEN b.start_block AND b.leaves_end_block"
            "   AND length(a.block)>%d",
            zTab, zTab, pgsz-45);
  n = 0;
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    n = sqlite3_column_int(pStmt, 0);
  }
  sqlite3_finalize(pStmt);
  nLeaf = nSeg - nIdx;
  printf("Leaf segments larger than %5d bytes.... %9d   %5.2f%%\n",
         pgsz-45, n, nLeaf>0 ? n*100.0/nLeaf : 0.0);

  pStmt = prepare(db, "SELECT max(level%%1024) FROM '%q_segdir'", zTab);
  mxLevel = 0;
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    mxLevel = sqlite3_column_int(pStmt, 0);
  }
  sqlite3_finalize(pStmt);

  for(i=0; i<=mxLevel; i++){
    pStmt = prepare(db,
           "SELECT count(*), sum(len), avg(len), max(len), sum(len>%d),"
           "       count(distinct idx)"
           "  FROM (SELECT length(a.block) AS len, idx"
           "          FROM '%q_segments' a JOIN '%q_segdir' b"
           "         WHERE (a.blockid BETWEEN b.start_block"
                                       " AND b.leaves_end_block)"
           "           AND (b.level%%1024)==%d)",
           pgsz-45, zTab, zTab, i);
    if( sqlite3_step(pStmt)==SQLITE_ROW
     && (nLeaf = sqlite3_column_int(pStmt, 0))>0
    ){
      sqlite3_int64 sz;
      nIdx = sqlite3_column_int(pStmt, 5);
      printf("For level %d:\n", i);
      printf("  Number of indexes...................... %9d\n", nIdx);
      printf("  Number of leaf segments................ %9d\n", nLeaf);
      if( nIdx>1 ){
        printf("  Average leaf segments per index........ %11.1f\n",
               (double)nLeaf/(double)nIdx);
      }
      printf("  Total size of all leaf segments........ %9lld\n",
             (sz = sqlite3_column_int64(pStmt, 1)));
      printf("  Average size of leaf segments.......... %11.1f\n",
             sqlite3_column_double(pStmt, 2));
      if( nIdx>1 ){
        printf("  Average leaf segment size per index.... %11.1f\n",
               (double)sz/(double)nIdx);
      }
      printf("  Maximum leaf segment size.............. %9lld\n",
             sqlite3_column_int64(pStmt, 3));
      n = sqlite3_column_int(pStmt, 4);
      printf("  Leaf segments larger than %5d bytes.. %9d   %5.2f%%\n",
             pgsz-45, n, n*100.0/nLeaf);
    }
    sqlite3_finalize(pStmt);
  }
}