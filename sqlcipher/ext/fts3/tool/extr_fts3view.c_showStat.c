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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
#define  SQLITE_BLOB 129 
#define  SQLITE_INTEGER 128 
 scalar_t__ SQLITE_ROW ; 
 int getVarint (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * prepare (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void showStat(sqlite3 *db, const char *zTab){
  sqlite3_stmt *pStmt;
  pStmt = prepare(db, "SELECT id, value FROM '%q_stat'", zTab);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    printf("stat[%d] =", sqlite3_column_int(pStmt, 0));
    switch( sqlite3_column_type(pStmt, 1) ){
      case SQLITE_INTEGER: {
        printf(" %d\n", sqlite3_column_int(pStmt, 1));
        break;
      }
      case SQLITE_BLOB: {
        unsigned char *x = (unsigned char*)sqlite3_column_blob(pStmt, 1);
        int len = sqlite3_column_bytes(pStmt, 1);
        int i = 0;
        sqlite3_int64 v;
        while( i<len ){
          i += getVarint(x, &v);
          printf(" %lld", v);
        }
        printf("\n");
        break;
      }
    }
  }
  sqlite3_finalize(pStmt);
}