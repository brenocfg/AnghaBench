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
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  scalar_t__ sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  BINARYLOG_FINALIZE ; 
 int /*<<< orphan*/  BINARYLOG_PREPARE_V2 ; 
 int /*<<< orphan*/  BINARYLOG_STEP ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 scalar_t__ sqlite3Hwtime () ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_instvfs_binarylog_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,char const*) ; 
 int /*<<< orphan*/  sqlite3_instvfs_binarylog_marker (int /*<<< orphan*/ *,char*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,char const**) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepareAndRun(sqlite3_vfs *pInstVfs, sqlite3 *db, const char *zSql){
  sqlite3_stmt *pStmt;
  const char *stmtTail;
  int rc;
  char zMessage[1024];
  zMessage[1023] = '\0';

  sqlite3_uint64 iTime;

  sqlite3_snprintf(1023, zMessage, "sqlite3_prepare_v2: %s", zSql);
  sqlite3_instvfs_binarylog_marker(pInstVfs, zMessage);

  iTime = sqlite3Hwtime();
  rc = sqlite3_prepare_v2(db, zSql, -1, &pStmt, &stmtTail);
  iTime = sqlite3Hwtime() - iTime;
  sqlite3_instvfs_binarylog_call(pInstVfs,BINARYLOG_PREPARE_V2,iTime,rc,zSql);

  if( rc==SQLITE_OK ){
    int nRow = 0;

    sqlite3_snprintf(1023, zMessage, "sqlite3_step loop: %s", zSql);
    sqlite3_instvfs_binarylog_marker(pInstVfs, zMessage);
    iTime = sqlite3Hwtime();
    while( (rc=sqlite3_step(pStmt))==SQLITE_ROW ){ nRow++; }
    iTime = sqlite3Hwtime() - iTime;
    sqlite3_instvfs_binarylog_call(pInstVfs, BINARYLOG_STEP, iTime, rc, zSql);

    sqlite3_snprintf(1023, zMessage, "sqlite3_finalize: %s", zSql);
    sqlite3_instvfs_binarylog_marker(pInstVfs, zMessage);
    iTime = sqlite3Hwtime();
    rc = sqlite3_finalize(pStmt);
    iTime = sqlite3Hwtime() - iTime;
    sqlite3_instvfs_binarylog_call(pInstVfs, BINARYLOG_FINALIZE, iTime, rc, zSql);
  }
}