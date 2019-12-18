#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  mDbFlags; TYPE_2__* aDb; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_17__ {scalar_t__ pSchema; scalar_t__ pTabSchema; struct TYPE_17__* pNext; } ;
typedef  TYPE_4__ Trigger ;
struct TYPE_18__ {TYPE_4__* pTrigger; } ;
typedef  TYPE_5__ Table ;
struct TYPE_15__ {TYPE_1__* pSchema; } ;
struct TYPE_14__ {int /*<<< orphan*/  trigHash; } ;
typedef  int /*<<< orphan*/  Hash ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_4__*) ; 
 int /*<<< orphan*/  DBFLAG_SchemaChange ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DeleteTrigger (TYPE_3__*,TYPE_4__*) ; 
 TYPE_4__* sqlite3HashInsert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SchemaMutexHeld (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* tableOfTrigger (TYPE_4__*) ; 

void sqlite3UnlinkAndDeleteTrigger(sqlite3 *db, int iDb, const char *zName){
  Trigger *pTrigger;
  Hash *pHash;

  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
  pHash = &(db->aDb[iDb].pSchema->trigHash);
  pTrigger = sqlite3HashInsert(pHash, zName, 0);
  if( ALWAYS(pTrigger) ){
    if( pTrigger->pSchema==pTrigger->pTabSchema ){
      Table *pTab = tableOfTrigger(pTrigger);
      Trigger **pp;
      for(pp=&pTab->pTrigger; *pp!=pTrigger; pp=&((*pp)->pNext));
      *pp = (*pp)->pNext;
    }
    sqlite3DeleteTrigger(db, pTrigger);
    db->mDbFlags |= DBFLAG_SchemaChange;
  }
}