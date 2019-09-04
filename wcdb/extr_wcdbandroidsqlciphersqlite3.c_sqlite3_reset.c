#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_8__ {int errMask; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_9__ {TYPE_1__* db; } ;
typedef  TYPE_2__ Vdbe ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  checkProfileCallback (TYPE_1__*,TYPE_2__*) ; 
 int sqlite3ApiExit (TYPE_1__*,int) ; 
 int sqlite3VdbeReset (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeRewind (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

int sqlite3_reset(sqlite3_stmt *pStmt){
  int rc;
  if( pStmt==0 ){
    rc = SQLITE_OK;
  }else{
    Vdbe *v = (Vdbe*)pStmt;
    sqlite3 *db = v->db;
    sqlite3_mutex_enter(db->mutex);
    checkProfileCallback(db, v);
    rc = sqlite3VdbeReset(v);
    sqlite3VdbeRewind(v);
    assert( (rc & (db->errMask))==rc );
    rc = sqlite3ApiExit(db, rc);
    sqlite3_mutex_leave(db->mutex);
  }
  return rc;
}