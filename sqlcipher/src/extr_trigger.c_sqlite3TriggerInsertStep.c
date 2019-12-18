#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  int /*<<< orphan*/  Upsert ;
struct TYPE_13__ {int /*<<< orphan*/  orconf; int /*<<< orphan*/ * pUpsert; int /*<<< orphan*/ * pIdList; int /*<<< orphan*/ * pSelect; } ;
typedef  TYPE_2__ TriggerStep ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_14__ {TYPE_1__* db; } ;
typedef  int /*<<< orphan*/  Select ;
typedef  TYPE_3__ Parse ;
typedef  int /*<<< orphan*/  IdList ;

/* Variables and functions */
 int /*<<< orphan*/  EXPRDUP_REDUCE ; 
 scalar_t__ IN_RENAME_OBJECT ; 
 int /*<<< orphan*/  TK_INSERT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3IdListDelete (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3SelectDelete (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3SelectDup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3UpsertDelete (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testcase (int /*<<< orphan*/ *) ; 
 TYPE_2__* triggerStepAllocate (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*) ; 

TriggerStep *sqlite3TriggerInsertStep(
  Parse *pParse,      /* Parser */
  Token *pTableName,  /* Name of the table into which we insert */
  IdList *pColumn,    /* List of columns in pTableName to insert into */
  Select *pSelect,    /* A SELECT statement that supplies values */
  u8 orconf,          /* The conflict algorithm (OE_Abort, OE_Replace, etc.) */
  Upsert *pUpsert,    /* ON CONFLICT clauses for upsert */
  const char *zStart, /* Start of SQL text */
  const char *zEnd    /* End of SQL text */
){
  sqlite3 *db = pParse->db;
  TriggerStep *pTriggerStep;

  assert(pSelect != 0 || db->mallocFailed);

  pTriggerStep = triggerStepAllocate(pParse, TK_INSERT, pTableName,zStart,zEnd);
  if( pTriggerStep ){
    if( IN_RENAME_OBJECT ){
      pTriggerStep->pSelect = pSelect;
      pSelect = 0;
    }else{
      pTriggerStep->pSelect = sqlite3SelectDup(db, pSelect, EXPRDUP_REDUCE);
    }
    pTriggerStep->pIdList = pColumn;
    pTriggerStep->pUpsert = pUpsert;
    pTriggerStep->orconf = orconf;
  }else{
    testcase( pColumn );
    sqlite3IdListDelete(db, pColumn);
    testcase( pUpsert );
    sqlite3UpsertDelete(db, pUpsert);
  }
  sqlite3SelectDelete(db, pSelect);

  return pTriggerStep;
}