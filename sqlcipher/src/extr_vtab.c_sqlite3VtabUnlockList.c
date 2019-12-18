#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mutex; TYPE_2__* pDisconnect; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_8__ {struct TYPE_8__* pNext; } ;
typedef  TYPE_2__ VTable ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeHoldsAllMutexes (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3ExpirePreparedStatements (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VtabUnlock (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3VtabUnlockList(sqlite3 *db){
  VTable *p = db->pDisconnect;
  db->pDisconnect = 0;

  assert( sqlite3BtreeHoldsAllMutexes(db) );
  assert( sqlite3_mutex_held(db->mutex) );

  if( p ){
    sqlite3ExpirePreparedStatements(db, 0);
    do {
      VTable *pNext = p->pNext;
      sqlite3VtabUnlock(p);
      p = pNext;
    }while( p );
  }
}