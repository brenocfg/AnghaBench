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
typedef  scalar_t__ sqlite_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 scalar_t__ finalizeTime ; 
 scalar_t__ prepTime ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ runTime ; 
 scalar_t__ sqlite3Hwtime () ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,char const**) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepareAndRun(sqlite3 *db, const char *zSql, int bQuiet){
  sqlite3_stmt *pStmt;
  const char *stmtTail;
  sqlite_uint64 iStart, iElapse;
  int rc;
  
  if (!bQuiet){
    printf("***************************************************************\n");
  }
  if (!bQuiet) printf("SQL statement: [%s]\n", zSql);
  iStart = sqlite3Hwtime();
  rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, &stmtTail);
  iElapse = sqlite3Hwtime() - iStart;
  prepTime += iElapse;
  if (!bQuiet){
    printf("sqlite3_prepare_v2() returns %d in %llu cycles\n", rc, iElapse);
  }
  if( rc==SQLITE_OK ){
    int nRow = 0;
    iStart = sqlite3Hwtime();
    while( (rc=sqlite3_step(pStmt))==SQLITE_ROW ){ nRow++; }
    iElapse = sqlite3Hwtime() - iStart;
    runTime += iElapse;
    if (!bQuiet){
      printf("sqlite3_step() returns %d after %d rows in %llu cycles\n",
             rc, nRow, iElapse);
    }
    iStart = sqlite3Hwtime();
    rc = sqlite3_finalize(pStmt);
    iElapse = sqlite3Hwtime() - iStart;
    finalizeTime += iElapse;
    if (!bQuiet){
      printf("sqlite3_finalize() returns %d in %llu cycles\n", rc, iElapse);
    }
  }
}