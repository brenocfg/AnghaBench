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

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int atoi (char*) ; 
 int atoi64 (char*) ; 
 char** azExtra ; 
 int /*<<< orphan*/  decodeDoclist (unsigned char const*,int) ; 
 scalar_t__ findOption (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * prepareToGetSegment (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  printBlob (unsigned char const*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 unsigned char* sqlite3_column_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void showDoclist(sqlite3 *db, const char *zTab){
  const unsigned char *aData;
  sqlite3_int64 offset;
  int nData;
  sqlite3_stmt *pStmt;

  offset = atoi64(azExtra[1]);
  nData = atoi(azExtra[2]);
  pStmt = prepareToGetSegment(db, zTab, azExtra[0]);
  if( sqlite3_step(pStmt)!=SQLITE_ROW ){
    sqlite3_finalize(pStmt);
    return;
  }
  aData = sqlite3_column_blob(pStmt, 0);
  printf("Doclist at %s offset %lld of size %d bytes:\n",
         azExtra[0], offset, nData);
  if( findOption("raw", 0, 0)!=0 ){
    printBlob(aData+offset, nData);
  }else{
    decodeDoclist(aData+offset, nData);
  }
  sqlite3_finalize(pStmt);
}