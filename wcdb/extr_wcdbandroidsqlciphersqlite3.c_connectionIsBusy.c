#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nDb; TYPE_1__* aDb; scalar_t__ pVdbe; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/ * pBt; } ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3BtreeIsInBackup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int connectionIsBusy(sqlite3 *db){
  int j;
  assert( sqlite3_mutex_held(db->mutex) );
  if( db->pVdbe ) return 1;
  for(j=0; j<db->nDb; j++){
    Btree *pBt = db->aDb[j].pBt;
    if( pBt && sqlite3BtreeIsInBackup(pBt) ) return 1;
  }
  return 0;
}