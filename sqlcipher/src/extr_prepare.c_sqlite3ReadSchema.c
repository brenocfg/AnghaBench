#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  busy; } ;
struct TYPE_7__ {int /*<<< orphan*/  mDbFlags; scalar_t__ noSharedCache; TYPE_1__ init; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_8__ {int rc; int /*<<< orphan*/  nErr; int /*<<< orphan*/  zErrMsg; TYPE_2__* db; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  DBFLAG_SchemaKnownOk ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int sqlite3Init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

int sqlite3ReadSchema(Parse *pParse){
  int rc = SQLITE_OK;
  sqlite3 *db = pParse->db;
  assert( sqlite3_mutex_held(db->mutex) );
  if( !db->init.busy ){
    rc = sqlite3Init(db, &pParse->zErrMsg);
    if( rc!=SQLITE_OK ){
      pParse->rc = rc;
      pParse->nErr++;
    }else if( db->noSharedCache ){
      db->mDbFlags |= DBFLAG_SchemaKnownOk;
    }
  }
  return rc;
}