#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nDb; scalar_t__ nSchemaLock; TYPE_1__* aDb; int /*<<< orphan*/  mDbFlags; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_7__ {int /*<<< orphan*/  pSchema; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBFLAG_SchemaKnownOk ; 
 int /*<<< orphan*/  DB_ResetWanted ; 
 scalar_t__ DbHasProperty (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbSetProperty (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3SchemaClear (int /*<<< orphan*/ ) ; 
 int sqlite3SchemaMutexHeld (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

void sqlite3ResetOneSchema(sqlite3 *db, int iDb){
  int i;
  assert( iDb<db->nDb );

  if( iDb>=0 ){
    assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
    DbSetProperty(db, iDb, DB_ResetWanted);
    DbSetProperty(db, 1, DB_ResetWanted);
    db->mDbFlags &= ~DBFLAG_SchemaKnownOk;
  }

  if( db->nSchemaLock==0 ){
    for(i=0; i<db->nDb; i++){
      if( DbHasProperty(db, i, DB_ResetWanted) ){
        sqlite3SchemaClear(db->aDb[i].pSchema);
      }
    }
  }
}