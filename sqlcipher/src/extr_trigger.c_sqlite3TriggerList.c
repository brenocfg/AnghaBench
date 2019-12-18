#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct TYPE_12__* pNext; int /*<<< orphan*/  table; TYPE_4__* const pTabSchema; } ;
typedef  TYPE_2__ Trigger ;
struct TYPE_13__ {TYPE_2__* pTrigger; int /*<<< orphan*/  zName; TYPE_4__* const pSchema; } ;
typedef  TYPE_3__ Table ;
struct TYPE_16__ {TYPE_1__* aDb; } ;
struct TYPE_15__ {TYPE_9__* db; scalar_t__ disableTriggers; } ;
struct TYPE_14__ {int /*<<< orphan*/  trigHash; } ;
struct TYPE_11__ {TYPE_4__* pSchema; } ;
typedef  TYPE_4__ Schema ;
typedef  TYPE_5__ Parse ;
typedef  int /*<<< orphan*/  HashElem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SchemaMutexHeld (TYPE_9__*,int /*<<< orphan*/ ,TYPE_4__* const) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqliteHashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashNext (int /*<<< orphan*/ *) ; 

Trigger *sqlite3TriggerList(Parse *pParse, Table *pTab){
  Schema * const pTmpSchema = pParse->db->aDb[1].pSchema;
  Trigger *pList = 0;                  /* List of triggers to return */

  if( pParse->disableTriggers ){
    return 0;
  }

  if( pTmpSchema!=pTab->pSchema ){
    HashElem *p;
    assert( sqlite3SchemaMutexHeld(pParse->db, 0, pTmpSchema) );
    for(p=sqliteHashFirst(&pTmpSchema->trigHash); p; p=sqliteHashNext(p)){
      Trigger *pTrig = (Trigger *)sqliteHashData(p);
      if( pTrig->pTabSchema==pTab->pSchema
       && 0==sqlite3StrICmp(pTrig->table, pTab->zName) 
      ){
        pTrig->pNext = (pList ? pList : pTab->pTrigger);
        pList = pTrig;
      }
    }
  }

  return (pList ? pList : pTab->pTrigger);
}