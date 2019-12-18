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
 int /*<<< orphan*/  atoi64 (char const*) ; 
 int /*<<< orphan*/ * prepare (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sqlite3_stmt *prepareToGetSegment(
  sqlite3 *db,         /* The database */
  const char *zTab,    /* The FTS3/4 table name */
  const char *zId      /* ID of the segment to open */
){
  sqlite3_stmt *pStmt;
  if( zId[0]=='r' ){
    pStmt = prepare(db, "SELECT root FROM '%q_segdir' WHERE rowid=%lld",
                    zTab, atoi64(zId+1));
  }else{
    pStmt = prepare(db, "SELECT block FROM '%q_segments' WHERE blockid=%lld",
                    zTab, atoi64(zId));
  }
  return pStmt;
}