#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {int /*<<< orphan*/  tabFlags; } ;
typedef  TYPE_1__ Table ;
struct TYPE_6__ {TYPE_1__* pEpoTab; } ;
typedef  TYPE_2__ Module ;

/* Variables and functions */
 int /*<<< orphan*/  TF_Ephemeral ; 
 int /*<<< orphan*/  sqlite3DeleteTable (int /*<<< orphan*/ *,TYPE_1__*) ; 

void sqlite3VtabEponymousTableClear(sqlite3 *db, Module *pMod){
  Table *pTab = pMod->pEpoTab;
  if( pTab!=0 ){
    /* Mark the table as Ephemeral prior to deleting it, so that the
    ** sqlite3DeleteTable() routine will know that it is not stored in 
    ** the schema. */
    pTab->tabFlags |= TF_Ephemeral;
    sqlite3DeleteTable(db, pTab);
    pMod->pEpoTab = 0;
  }
}