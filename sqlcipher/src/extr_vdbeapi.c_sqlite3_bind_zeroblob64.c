#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {TYPE_2__* db; } ;
typedef  TYPE_1__ Vdbe ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; scalar_t__* aLimit; } ;

/* Variables and functions */
 size_t SQLITE_LIMIT_LENGTH ; 
 int SQLITE_TOOBIG ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3ApiExit (TYPE_2__*,int) ; 
 int sqlite3_bind_zeroblob (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

int sqlite3_bind_zeroblob64(sqlite3_stmt *pStmt, int i, sqlite3_uint64 n){
  int rc;
  Vdbe *p = (Vdbe *)pStmt;
  sqlite3_mutex_enter(p->db->mutex);
  if( n>(u64)p->db->aLimit[SQLITE_LIMIT_LENGTH] ){
    rc = SQLITE_TOOBIG;
  }else{
    assert( (n & 0x7FFFFFFF)==n );
    rc = sqlite3_bind_zeroblob(pStmt, i, n);
  }
  rc = sqlite3ApiExit(p->db, rc);
  sqlite3_mutex_leave(p->db->mutex);
  return rc;
}