#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ pnBytesFreed; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_17__ {TYPE_7__* pSchema; TYPE_5__* pFKey; } ;
typedef  TYPE_4__ Table ;
struct TYPE_19__ {int /*<<< orphan*/  fkeyHash; } ;
struct TYPE_18__ {char* zTo; int isDeferred; struct TYPE_18__* pNextFrom; int /*<<< orphan*/ * apTrigger; TYPE_2__* pPrevTo; TYPE_1__* pNextTo; } ;
struct TYPE_15__ {TYPE_1__* pNextTo; } ;
struct TYPE_14__ {char* zTo; TYPE_2__* pPrevTo; } ;
typedef  TYPE_5__ FKey ;

/* Variables and functions */
 scalar_t__ IsVirtual (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fkTriggerDelete (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3HashInsert (int /*<<< orphan*/ *,char const*,void*) ; 
 scalar_t__ sqlite3SchemaMutexHeld (TYPE_3__*,int /*<<< orphan*/ ,TYPE_7__*) ; 

void sqlite3FkDelete(sqlite3 *db, Table *pTab){
  FKey *pFKey;                    /* Iterator variable */
  FKey *pNext;                    /* Copy of pFKey->pNextFrom */

  assert( db==0 || IsVirtual(pTab)
         || sqlite3SchemaMutexHeld(db, 0, pTab->pSchema) );
  for(pFKey=pTab->pFKey; pFKey; pFKey=pNext){

    /* Remove the FK from the fkeyHash hash table. */
    if( !db || db->pnBytesFreed==0 ){
      if( pFKey->pPrevTo ){
        pFKey->pPrevTo->pNextTo = pFKey->pNextTo;
      }else{
        void *p = (void *)pFKey->pNextTo;
        const char *z = (p ? pFKey->pNextTo->zTo : pFKey->zTo);
        sqlite3HashInsert(&pTab->pSchema->fkeyHash, z, p);
      }
      if( pFKey->pNextTo ){
        pFKey->pNextTo->pPrevTo = pFKey->pPrevTo;
      }
    }

    /* EV: R-30323-21917 Each foreign key constraint in SQLite is
    ** classified as either immediate or deferred.
    */
    assert( pFKey->isDeferred==0 || pFKey->isDeferred==1 );

    /* Delete any triggers created to implement actions for this FK. */
#ifndef SQLITE_OMIT_TRIGGER
    fkTriggerDelete(db, pFKey->apTrigger[0]);
    fkTriggerDelete(db, pFKey->apTrigger[1]);
#endif

    pNext = pFKey->pNextFrom;
    sqlite3DbFree(db, pFKey);
  }
}