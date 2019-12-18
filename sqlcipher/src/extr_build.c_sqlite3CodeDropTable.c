#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_5__* aDb; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_23__ {scalar_t__ pSchema; struct TYPE_23__* pNext; } ;
typedef  TYPE_2__ Trigger ;
struct TYPE_24__ {scalar_t__ pSchema; int tabFlags; int /*<<< orphan*/  zName; } ;
typedef  TYPE_3__ Table ;
struct TYPE_26__ {scalar_t__ pSchema; int /*<<< orphan*/  zDbSName; } ;
struct TYPE_25__ {TYPE_1__* db; } ;
typedef  TYPE_4__ Parse ;
typedef  TYPE_5__ Db ;

/* Variables and functions */
 scalar_t__ IsVirtual (TYPE_3__*) ; 
 int /*<<< orphan*/  MASTER_NAME ; 
 int /*<<< orphan*/  OP_DropTable ; 
 int /*<<< orphan*/  OP_VBegin ; 
 int /*<<< orphan*/  OP_VDestroy ; 
 int TF_Autoincrement ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  destroyTable (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3BeginWriteOperation (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ChangeCookie (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sqlite3DropTriggerPtr (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3MayAbort (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3NestedParse (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_2__* sqlite3TriggerList (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqliteViewResetAll (TYPE_1__*,int) ; 

void sqlite3CodeDropTable(Parse *pParse, Table *pTab, int iDb, int isView){
  Vdbe *v;
  sqlite3 *db = pParse->db;
  Trigger *pTrigger;
  Db *pDb = &db->aDb[iDb];

  v = sqlite3GetVdbe(pParse);
  assert( v!=0 );
  sqlite3BeginWriteOperation(pParse, 1, iDb);

#ifndef SQLITE_OMIT_VIRTUALTABLE
  if( IsVirtual(pTab) ){
    sqlite3VdbeAddOp0(v, OP_VBegin);
  }
#endif

  /* Drop all triggers associated with the table being dropped. Code
  ** is generated to remove entries from sqlite_master and/or
  ** sqlite_temp_master if required.
  */
  pTrigger = sqlite3TriggerList(pParse, pTab);
  while( pTrigger ){
    assert( pTrigger->pSchema==pTab->pSchema || 
        pTrigger->pSchema==db->aDb[1].pSchema );
    sqlite3DropTriggerPtr(pParse, pTrigger);
    pTrigger = pTrigger->pNext;
  }

#ifndef SQLITE_OMIT_AUTOINCREMENT
  /* Remove any entries of the sqlite_sequence table associated with
  ** the table being dropped. This is done before the table is dropped
  ** at the btree level, in case the sqlite_sequence table needs to
  ** move as a result of the drop (can happen in auto-vacuum mode).
  */
  if( pTab->tabFlags & TF_Autoincrement ){
    sqlite3NestedParse(pParse,
      "DELETE FROM %Q.sqlite_sequence WHERE name=%Q",
      pDb->zDbSName, pTab->zName
    );
  }
#endif

  /* Drop all SQLITE_MASTER table and index entries that refer to the
  ** table. The program name loops through the master table and deletes
  ** every row that refers to a table of the same name as the one being
  ** dropped. Triggers are handled separately because a trigger can be
  ** created in the temp database that refers to a table in another
  ** database.
  */
  sqlite3NestedParse(pParse, 
      "DELETE FROM %Q.%s WHERE tbl_name=%Q and type!='trigger'",
      pDb->zDbSName, MASTER_NAME, pTab->zName);
  if( !isView && !IsVirtual(pTab) ){
    destroyTable(pParse, pTab);
  }

  /* Remove the table entry from SQLite's internal schema and modify
  ** the schema cookie.
  */
  if( IsVirtual(pTab) ){
    sqlite3VdbeAddOp4(v, OP_VDestroy, iDb, 0, 0, pTab->zName, 0);
    sqlite3MayAbort(pParse);
  }
  sqlite3VdbeAddOp4(v, OP_DropTable, iDb, 0, 0, pTab->zName, 0);
  sqlite3ChangeCookie(pParse, iDb);
  sqliteViewResetAll(db, iDb);
}