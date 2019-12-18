#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/  rcErr; } ;
typedef  TYPE_1__ ScrubState ;

/* Variables and functions */
 int /*<<< orphan*/  scrubBackupErr (TYPE_1__*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sqlite3_stmt *scrubBackupPrepare(
  ScrubState *p,      /* Backup context */
  sqlite3 *db,        /* Database to prepare against */
  const char *zSql    /* SQL statement */
){
  sqlite3_stmt *pStmt;
  if( p->rcErr ) return 0;
  p->rcErr = sqlite3_prepare_v2(db, zSql, -1, &pStmt, 0);
  if( p->rcErr ){
    scrubBackupErr(p, "SQL error \"%s\" on \"%s\"",
                   sqlite3_errmsg(db), zSql);
    sqlite3_finalize(pStmt);
    return 0;
  }
  return pStmt;
}