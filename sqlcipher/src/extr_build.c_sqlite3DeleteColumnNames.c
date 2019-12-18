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
struct TYPE_5__ {int nCol; TYPE_2__* aCol; } ;
typedef  TYPE_1__ Table ;
struct TYPE_6__ {struct TYPE_6__* zColl; int /*<<< orphan*/  pDflt; struct TYPE_6__* zName; } ;
typedef  TYPE_2__ Column ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3DeleteColumnNames(sqlite3 *db, Table *pTable){
  int i;
  Column *pCol;
  assert( pTable!=0 );
  if( (pCol = pTable->aCol)!=0 ){
    for(i=0; i<pTable->nCol; i++, pCol++){
      sqlite3DbFree(db, pCol->zName);
      sqlite3ExprDelete(db, pCol->pDflt);
      sqlite3DbFree(db, pCol->zColl);
    }
    sqlite3DbFree(db, pTable->aCol);
  }
}