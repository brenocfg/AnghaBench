#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_12__ ;

/* Type definitions */
struct TYPE_36__ {scalar_t__ busy; } ;
struct TYPE_39__ {TYPE_3__* aDb; TYPE_1__ init; } ;
typedef  TYPE_4__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_40__ {struct TYPE_40__* pNext; TYPE_6__* pTrig; } ;
typedef  TYPE_5__ TriggerStep ;
struct TYPE_41__ {char* zName; struct TYPE_41__* pNext; int /*<<< orphan*/  table; TYPE_12__* pTabSchema; TYPE_12__* pSchema; int /*<<< orphan*/  pWhen; TYPE_5__* step_list; } ;
typedef  TYPE_6__ Trigger ;
struct TYPE_42__ {int /*<<< orphan*/  n; scalar_t__ z; } ;
typedef  TYPE_7__ Token ;
struct TYPE_43__ {TYPE_6__* pTrigger; } ;
typedef  TYPE_8__ Table ;
struct TYPE_44__ {TYPE_6__* pNewTrigger; TYPE_4__* db; int /*<<< orphan*/  nErr; } ;
struct TYPE_38__ {TYPE_2__* pSchema; int /*<<< orphan*/  zDbSName; } ;
struct TYPE_37__ {int /*<<< orphan*/  trigHash; } ;
struct TYPE_35__ {int /*<<< orphan*/  tblHash; } ;
typedef  TYPE_9__ Parse ;
typedef  int /*<<< orphan*/  Hash ;
typedef  int /*<<< orphan*/  DbFixer ;

/* Variables and functions */
 scalar_t__ IN_RENAME_OBJECT ; 
 int /*<<< orphan*/  MASTER_NAME ; 
 scalar_t__ NEVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3BeginWriteOperation (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3ChangeCookie (TYPE_9__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_4__*,char*) ; 
 char* sqlite3DbStrNDup (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DeleteTrigger (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3DeleteTriggerStep (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ sqlite3FixExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3FixInit (int /*<<< orphan*/ *,TYPE_9__*,int,char*,TYPE_7__*) ; 
 scalar_t__ sqlite3FixTriggerStep (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_9__*) ; 
 TYPE_8__* sqlite3HashFind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* sqlite3HashInsert (int /*<<< orphan*/ *,char*,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3MPrintf (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  sqlite3NestedParse (TYPE_9__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3OomFault (TYPE_4__*) ; 
 int sqlite3SchemaMutexHeld (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int sqlite3SchemaToIndex (TYPE_4__*,TYPE_12__*) ; 
 int /*<<< orphan*/  sqlite3TokenInit (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddParseSchemaOp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

void sqlite3FinishTrigger(
  Parse *pParse,          /* Parser context */
  TriggerStep *pStepList, /* The triggered program */
  Token *pAll             /* Token that describes the complete CREATE TRIGGER */
){
  Trigger *pTrig = pParse->pNewTrigger;   /* Trigger being finished */
  char *zName;                            /* Name of trigger */
  sqlite3 *db = pParse->db;               /* The database */
  DbFixer sFix;                           /* Fixer object */
  int iDb;                                /* Database containing the trigger */
  Token nameToken;                        /* Trigger name for error reporting */

  pParse->pNewTrigger = 0;
  if( NEVER(pParse->nErr) || !pTrig ) goto triggerfinish_cleanup;
  zName = pTrig->zName;
  iDb = sqlite3SchemaToIndex(pParse->db, pTrig->pSchema);
  pTrig->step_list = pStepList;
  while( pStepList ){
    pStepList->pTrig = pTrig;
    pStepList = pStepList->pNext;
  }
  sqlite3TokenInit(&nameToken, pTrig->zName);
  sqlite3FixInit(&sFix, pParse, iDb, "trigger", &nameToken);
  if( sqlite3FixTriggerStep(&sFix, pTrig->step_list) 
   || sqlite3FixExpr(&sFix, pTrig->pWhen) 
  ){
    goto triggerfinish_cleanup;
  }

#ifndef SQLITE_OMIT_ALTERTABLE
  if( IN_RENAME_OBJECT ){
    assert( !db->init.busy );
    pParse->pNewTrigger = pTrig;
    pTrig = 0;
  }else
#endif

  /* if we are not initializing,
  ** build the sqlite_master entry
  */
  if( !db->init.busy ){
    Vdbe *v;
    char *z;

    /* Make an entry in the sqlite_master table */
    v = sqlite3GetVdbe(pParse);
    if( v==0 ) goto triggerfinish_cleanup;
    sqlite3BeginWriteOperation(pParse, 0, iDb);
    z = sqlite3DbStrNDup(db, (char*)pAll->z, pAll->n);
    testcase( z==0 );
    sqlite3NestedParse(pParse,
       "INSERT INTO %Q.%s VALUES('trigger',%Q,%Q,0,'CREATE TRIGGER %q')",
       db->aDb[iDb].zDbSName, MASTER_NAME, zName,
       pTrig->table, z);
    sqlite3DbFree(db, z);
    sqlite3ChangeCookie(pParse, iDb);
    sqlite3VdbeAddParseSchemaOp(v, iDb,
        sqlite3MPrintf(db, "type='trigger' AND name='%q'", zName));
  }

  if( db->init.busy ){
    Trigger *pLink = pTrig;
    Hash *pHash = &db->aDb[iDb].pSchema->trigHash;
    assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
    pTrig = sqlite3HashInsert(pHash, zName, pTrig);
    if( pTrig ){
      sqlite3OomFault(db);
    }else if( pLink->pSchema==pLink->pTabSchema ){
      Table *pTab;
      pTab = sqlite3HashFind(&pLink->pTabSchema->tblHash, pLink->table);
      assert( pTab!=0 );
      pLink->pNext = pTab->pTrigger;
      pTab->pTrigger = pLink;
    }
  }

triggerfinish_cleanup:
  sqlite3DeleteTrigger(db, pTrig);
  assert( IN_RENAME_OBJECT || !pParse->pNewTrigger );
  sqlite3DeleteTriggerStep(db, pStepList);
}