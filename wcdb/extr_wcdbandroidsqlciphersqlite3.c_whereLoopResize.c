#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  WhereTerm ;
struct TYPE_3__ {int nLSlot; int /*<<< orphan*/ ** aLTerm; int /*<<< orphan*/ ** aLTermSpace; } ;
typedef  TYPE_1__ WhereLoop ;

/* Variables and functions */
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** sqlite3DbMallocRawNN (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int whereLoopResize(sqlite3 *db, WhereLoop *p, int n){
  WhereTerm **paNew;
  if( p->nLSlot>=n ) return SQLITE_OK;
  n = (n+7)&~7;
  paNew = sqlite3DbMallocRawNN(db, sizeof(p->aLTerm[0])*n);
  if( paNew==0 ) return SQLITE_NOMEM_BKPT;
  memcpy(paNew, p->aLTerm, sizeof(p->aLTerm[0])*p->nLSlot);
  if( p->aLTerm!=p->aLTermSpace ) sqlite3DbFreeNN(db, p->aLTerm);
  p->aLTerm = paNew;
  p->nLSlot = n;
  return SQLITE_OK;
}