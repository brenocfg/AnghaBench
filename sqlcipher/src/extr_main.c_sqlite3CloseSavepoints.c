#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ isTransactionSavepoint; scalar_t__ nStatement; scalar_t__ nSavepoint; TYPE_2__* pSavepoint; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ Savepoint ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,TYPE_2__*) ; 

void sqlite3CloseSavepoints(sqlite3 *db){
  while( db->pSavepoint ){
    Savepoint *pTmp = db->pSavepoint;
    db->pSavepoint = pTmp->pNext;
    sqlite3DbFree(db, pTmp);
  }
  db->nSavepoint = 0;
  db->nStatement = 0;
  db->isTransactionSavepoint = 0;
}