#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int fts3DoOptimize (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3Fts3SegmentsClose (TYPE_1__*) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3Fts3Optimize(Fts3Table *p){
  int rc;
  rc = sqlite3_exec(p->db, "SAVEPOINT fts3", 0, 0, 0);
  if( rc==SQLITE_OK ){
    rc = fts3DoOptimize(p, 1);
    if( rc==SQLITE_OK || rc==SQLITE_DONE ){
      int rc2 = sqlite3_exec(p->db, "RELEASE fts3", 0, 0, 0);
      if( rc2!=SQLITE_OK ) rc = rc2;
    }else{
      sqlite3_exec(p->db, "ROLLBACK TO fts3", 0, 0, 0);
      sqlite3_exec(p->db, "RELEASE fts3", 0, 0, 0);
    }
  }
  sqlite3Fts3SegmentsClose(p);
  return rc;
}