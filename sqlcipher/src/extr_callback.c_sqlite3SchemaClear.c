#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Trigger ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_2__ {int schemaFlags; int /*<<< orphan*/  iGeneration; scalar_t__ pSeqTab; int /*<<< orphan*/  fkeyHash; int /*<<< orphan*/  tblHash; int /*<<< orphan*/  idxHash; int /*<<< orphan*/  trigHash; } ;
typedef  TYPE_1__ Schema ;
typedef  int /*<<< orphan*/  HashElem ;
typedef  int /*<<< orphan*/  Hash ;

/* Variables and functions */
 int DB_ResetWanted ; 
 int DB_SchemaLoaded ; 
 int /*<<< orphan*/  sqlite3DeleteTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3DeleteTrigger (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3HashClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3HashInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashNext (int /*<<< orphan*/ *) ; 

void sqlite3SchemaClear(void *p){
  Hash temp1;
  Hash temp2;
  HashElem *pElem;
  Schema *pSchema = (Schema *)p;

  temp1 = pSchema->tblHash;
  temp2 = pSchema->trigHash;
  sqlite3HashInit(&pSchema->trigHash);
  sqlite3HashClear(&pSchema->idxHash);
  for(pElem=sqliteHashFirst(&temp2); pElem; pElem=sqliteHashNext(pElem)){
    sqlite3DeleteTrigger(0, (Trigger*)sqliteHashData(pElem));
  }
  sqlite3HashClear(&temp2);
  sqlite3HashInit(&pSchema->tblHash);
  for(pElem=sqliteHashFirst(&temp1); pElem; pElem=sqliteHashNext(pElem)){
    Table *pTab = sqliteHashData(pElem);
    sqlite3DeleteTable(0, pTab);
  }
  sqlite3HashClear(&temp1);
  sqlite3HashClear(&pSchema->fkeyHash);
  pSchema->pSeqTab = 0;
  if( pSchema->schemaFlags & DB_SchemaLoaded ){
    pSchema->iGeneration++;
  }
  pSchema->schemaFlags &= ~(DB_SchemaLoaded|DB_ResetWanted);
}