#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nFreeSlot; int bUnderPressure; scalar_t__ nReserve; scalar_t__ nSlot; int /*<<< orphan*/  mutex; TYPE_1__* pFree; int /*<<< orphan*/  pEnd; int /*<<< orphan*/  pStart; } ;
struct TYPE_3__ {struct TYPE_3__* pNext; } ;
typedef  TYPE_1__ PgFreeslot ;

/* Variables and functions */
 int /*<<< orphan*/  MEMTYPE_HEAP ; 
 int /*<<< orphan*/  MEMTYPE_PCACHE ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_OVERFLOW ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_USED ; 
 scalar_t__ SQLITE_WITHIN (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ pcache1 ; 
 int sqlite3MallocSize (void*) ; 
 int sqlite3MemdebugHasType (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3MemdebugSetType (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3StatusDown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcache1Free(void *p){
  if( p==0 ) return;
  if( SQLITE_WITHIN(p, pcache1.pStart, pcache1.pEnd) ){
    PgFreeslot *pSlot;
    sqlite3_mutex_enter(pcache1.mutex);
    sqlite3StatusDown(SQLITE_STATUS_PAGECACHE_USED, 1);
    pSlot = (PgFreeslot*)p;
    pSlot->pNext = pcache1.pFree;
    pcache1.pFree = pSlot;
    pcache1.nFreeSlot++;
    pcache1.bUnderPressure = pcache1.nFreeSlot<pcache1.nReserve;
    assert( pcache1.nFreeSlot<=pcache1.nSlot );
    sqlite3_mutex_leave(pcache1.mutex);
  }else{
    assert( sqlite3MemdebugHasType(p, MEMTYPE_PCACHE) );
    sqlite3MemdebugSetType(p, MEMTYPE_HEAP);
#ifndef SQLITE_DISABLE_PAGECACHE_OVERFLOW_STATS
    {
      int nFreed = 0;
      nFreed = sqlite3MallocSize(p);
      sqlite3_mutex_enter(pcache1.mutex);
      sqlite3StatusDown(SQLITE_STATUS_PAGECACHE_OVERFLOW, nFreed);
      sqlite3_mutex_leave(pcache1.mutex);
    }
#endif
    sqlite3_free(p);
  }
}