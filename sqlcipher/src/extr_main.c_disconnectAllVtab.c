#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int nDb; int /*<<< orphan*/  aModule; TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_14__ {int /*<<< orphan*/ * pEpoTab; } ;
struct TYPE_13__ {int /*<<< orphan*/  tblHash; } ;
struct TYPE_11__ {TYPE_3__* pSchema; } ;
typedef  TYPE_3__ Schema ;
typedef  TYPE_4__ Module ;
typedef  int /*<<< orphan*/  HashElem ;

/* Variables and functions */
 scalar_t__ IsVirtual (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BtreeEnterAll (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeaveAll (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VtabDisconnect (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VtabUnlockList (TYPE_2__*) ; 
 scalar_t__ sqliteHashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashNext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disconnectAllVtab(sqlite3 *db){
#ifndef SQLITE_OMIT_VIRTUALTABLE
  int i;
  HashElem *p;
  sqlite3BtreeEnterAll(db);
  for(i=0; i<db->nDb; i++){
    Schema *pSchema = db->aDb[i].pSchema;
    if( pSchema ){
      for(p=sqliteHashFirst(&pSchema->tblHash); p; p=sqliteHashNext(p)){
        Table *pTab = (Table *)sqliteHashData(p);
        if( IsVirtual(pTab) ) sqlite3VtabDisconnect(db, pTab);
      }
    }
  }
  for(p=sqliteHashFirst(&db->aModule); p; p=sqliteHashNext(p)){
    Module *pMod = (Module *)sqliteHashData(p);
    if( pMod->pEpoTab ){
      sqlite3VtabDisconnect(db, pMod->pEpoTab);
    }
  }
  sqlite3VtabUnlockList(db);
  sqlite3BtreeLeaveAll(db);
#else
  UNUSED_PARAMETER(db);
#endif
}