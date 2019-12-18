#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int nDb; TYPE_3__* aDb; scalar_t__ mallocFailed; } ;
typedef  TYPE_4__ sqlite3 ;
typedef  int /*<<< orphan*/  Trigger ;
struct TYPE_23__ {int checkSchema; TYPE_4__* db; } ;
struct TYPE_22__ {int nSrc; TYPE_1__* a; } ;
struct TYPE_20__ {TYPE_2__* pSchema; int /*<<< orphan*/  zDbSName; } ;
struct TYPE_19__ {int /*<<< orphan*/  trigHash; } ;
struct TYPE_18__ {char* zDatabase; char* zName; } ;
typedef  TYPE_5__ SrcList ;
typedef  TYPE_6__ Parse ;

/* Variables and functions */
 int OMIT_TEMPDB ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3BtreeHoldsAllMutexes (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3CodeVerifyNamedSchema (TYPE_6__*,char const*) ; 
 int /*<<< orphan*/  sqlite3DropTriggerPtr (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_6__*,char*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3HashFind (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ sqlite3ReadSchema (TYPE_6__*) ; 
 int sqlite3SchemaMutexHeld (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,char const*) ; 

void sqlite3DropTrigger(Parse *pParse, SrcList *pName, int noErr){
  Trigger *pTrigger = 0;
  int i;
  const char *zDb;
  const char *zName;
  sqlite3 *db = pParse->db;

  if( db->mallocFailed ) goto drop_trigger_cleanup;
  if( SQLITE_OK!=sqlite3ReadSchema(pParse) ){
    goto drop_trigger_cleanup;
  }

  assert( pName->nSrc==1 );
  zDb = pName->a[0].zDatabase;
  zName = pName->a[0].zName;
  assert( zDb!=0 || sqlite3BtreeHoldsAllMutexes(db) );
  for(i=OMIT_TEMPDB; i<db->nDb; i++){
    int j = (i<2) ? i^1 : i;  /* Search TEMP before MAIN */
    if( zDb && sqlite3StrICmp(db->aDb[j].zDbSName, zDb) ) continue;
    assert( sqlite3SchemaMutexHeld(db, j, 0) );
    pTrigger = sqlite3HashFind(&(db->aDb[j].pSchema->trigHash), zName);
    if( pTrigger ) break;
  }
  if( !pTrigger ){
    if( !noErr ){
      sqlite3ErrorMsg(pParse, "no such trigger: %S", pName, 0);
    }else{
      sqlite3CodeVerifyNamedSchema(pParse, zDb);
    }
    pParse->checkSchema = 1;
    goto drop_trigger_cleanup;
  }
  sqlite3DropTriggerPtr(pParse, pTrigger);

drop_trigger_cleanup:
  sqlite3SrcListDelete(db, pName);
}