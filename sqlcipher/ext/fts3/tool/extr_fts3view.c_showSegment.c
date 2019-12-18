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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 char** azExtra ; 
 int /*<<< orphan*/  decodeSegment (unsigned char const*,int) ; 
 scalar_t__ findOption (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * prepareToGetSegment (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  printBlob (unsigned char const*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 unsigned char* sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void showSegment(sqlite3 *db, const char *zTab){
  const unsigned char *aData;
  int nData;
  sqlite3_stmt *pStmt;

  pStmt = prepareToGetSegment(db, zTab, azExtra[0]);
  if( sqlite3_step(pStmt)!=SQLITE_ROW ){
    sqlite3_finalize(pStmt);
    return;
  }
  nData = sqlite3_column_bytes(pStmt, 0);
  aData = sqlite3_column_blob(pStmt, 0);
  printf("Segment %s of size %d bytes:\n", azExtra[0], nData);
  if( findOption("raw", 0, 0)!=0 ){
    printBlob(aData, nData);
  }else{
    decodeSegment(aData, nData);
  }
  sqlite3_finalize(pStmt);
}