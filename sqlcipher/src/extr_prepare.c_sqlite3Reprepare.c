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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3LockAndPrepare (TYPE_1__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3OomFault (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3TransferBindings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* sqlite3VdbeDb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeFinalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbePrepareFlags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResetStepResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeSwap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 char* sqlite3_sql (int /*<<< orphan*/ *) ; 

int sqlite3Reprepare(Vdbe *p){
  int rc;
  sqlite3_stmt *pNew;
  const char *zSql;
  sqlite3 *db;
  u8 prepFlags;

  assert( sqlite3_mutex_held(sqlite3VdbeDb(p)->mutex) );
  zSql = sqlite3_sql((sqlite3_stmt *)p);
  assert( zSql!=0 );  /* Reprepare only called for prepare_v2() statements */
  db = sqlite3VdbeDb(p);
  assert( sqlite3_mutex_held(db->mutex) );
  prepFlags = sqlite3VdbePrepareFlags(p);
  rc = sqlite3LockAndPrepare(db, zSql, -1, prepFlags, p, &pNew, 0);
  if( rc ){
    if( rc==SQLITE_NOMEM ){
      sqlite3OomFault(db);
    }
    assert( pNew==0 );
    return rc;
  }else{
    assert( pNew!=0 );
  }
  sqlite3VdbeSwap((Vdbe*)pNew, p);
  sqlite3TransferBindings(pNew, (sqlite3_stmt*)p);
  sqlite3VdbeResetStepResult((Vdbe*)pNew);
  sqlite3VdbeFinalize((Vdbe*)pNew);
  return SQLITE_OK;
}