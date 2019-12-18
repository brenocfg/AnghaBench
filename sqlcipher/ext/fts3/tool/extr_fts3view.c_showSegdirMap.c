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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  rtag ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 scalar_t__ isNullSegment (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * prepare (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  printTreeLine (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void showSegdirMap(sqlite3 *db, const char *zTab){
  int mxIndex, iIndex;
  sqlite3_stmt *pStmt = 0;
  sqlite3_stmt *pStmt2 = 0;
  int prevLevel;

  pStmt = prepare(db, "SELECT max(level/1024) FROM '%q_segdir'", zTab);
  if( sqlite3_step(pStmt)==SQLITE_ROW ){
    mxIndex = sqlite3_column_int(pStmt, 0);
  }else{
    mxIndex = 0;
  }
  sqlite3_finalize(pStmt);

  printf("Number of inverted indices............... %3d\n", mxIndex+1);
  pStmt = prepare(db,
    "SELECT level, idx, start_block, leaves_end_block, end_block, rowid"
    "  FROM '%q_segdir'"
    " WHERE level/1024==?"
    " ORDER BY level DESC, idx",
    zTab);
  pStmt2 = prepare(db,
    "SELECT blockid FROM '%q_segments'"
    " WHERE blockid BETWEEN ? AND ? ORDER BY blockid",
    zTab);
  for(iIndex=0; iIndex<=mxIndex; iIndex++){
    if( mxIndex>0 ){
      printf("**************************** Index %d "
             "****************************\n", iIndex);
    }
    sqlite3_bind_int(pStmt, 1, iIndex);
    prevLevel = -1;
    while( sqlite3_step(pStmt)==SQLITE_ROW ){
      int iLevel = sqlite3_column_int(pStmt, 0)%1024;
      int iIdx = sqlite3_column_int(pStmt, 1);
      sqlite3_int64 iStart = sqlite3_column_int64(pStmt, 2);
      sqlite3_int64 iLEnd = sqlite3_column_int64(pStmt, 3);
      sqlite3_int64 iEnd = sqlite3_column_int64(pStmt, 4);
      char rtag[20];
      if( iLevel!=prevLevel ){
        printf("level %2d idx %2d", iLevel, iIdx);
        prevLevel = iLevel;
      }else{
        printf("         idx %2d", iIdx);
      }
      sqlite3_snprintf(sizeof(rtag), rtag, "r%lld",
                       sqlite3_column_int64(pStmt,5));
      printf("  root   %9s\n", rtag);
      if( iLEnd>iStart ){
        sqlite3_int64 iLower, iPrev = 0, iX;
        if( iLEnd+1<=iEnd ){
          sqlite3_bind_int64(pStmt2, 1, iLEnd+1);
          sqlite3_bind_int64(pStmt2, 2, iEnd);
          iLower = -1;        
          while( sqlite3_step(pStmt2)==SQLITE_ROW ){
            iX = sqlite3_column_int64(pStmt2, 0);
            if( iLower<0 ){
              iLower = iPrev = iX;
            }else if( iX==iPrev+1 ){
              iPrev = iX;
            }else{
              printTreeLine(iLower, iPrev);
              iLower = iPrev = iX;
            }
          }
          sqlite3_reset(pStmt2);
          if( iLower>=0 ){
            if( iLower==iPrev && iLower==iEnd
             && isNullSegment(db,zTab,iLower)
            ){
              printf("                 null   %9lld\n", iLower);
            }else{
              printTreeLine(iLower, iPrev);
            }
          }
        }
        printf("                 leaves %9lld thru %9lld  (%lld blocks)\n",
               iStart, iLEnd, iLEnd - iStart + 1);
      }
    }
    sqlite3_reset(pStmt);
  }
  sqlite3_finalize(pStmt);
  sqlite3_finalize(pStmt2);
}