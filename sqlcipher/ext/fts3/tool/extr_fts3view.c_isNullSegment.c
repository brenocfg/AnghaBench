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
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/ * prepare (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isNullSegment(sqlite3 *db, const char *zTab, sqlite3_int64 iBlockId){
  sqlite3_stmt *pStmt;
  int rc = 1;

  pStmt = prepare(db, "SELECT block IS NULL FROM '%q_segments'"
                      " WHERE blockid=%lld", zTab, iBlockId);
  if( sqlite3_step(pStmt)==SQLITE_ROW ){
    rc = sqlite3_column_int(pStmt, 0);
  }
  sqlite3_finalize(pStmt);
  return rc;
}