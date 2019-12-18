#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_6__ {scalar_t__ bDisable; scalar_t__ sz; int /*<<< orphan*/ * anStat; TYPE_3__* pInit; TYPE_3__* pFree; } ;
struct TYPE_7__ {scalar_t__ pnBytesFreed; scalar_t__ mallocFailed; int /*<<< orphan*/  mutex; TYPE_1__ lookaside; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_8__ {struct TYPE_8__* pNext; } ;
typedef  TYPE_3__ LookasideSlot ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* dbMallocRawFinish (TYPE_2__*,scalar_t__) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void *sqlite3DbMallocRawNN(sqlite3 *db, u64 n){
#ifndef SQLITE_OMIT_LOOKASIDE
  LookasideSlot *pBuf;
  assert( db!=0 );
  assert( sqlite3_mutex_held(db->mutex) );
  assert( db->pnBytesFreed==0 );
  if( db->lookaside.bDisable==0 ){
    assert( db->mallocFailed==0 );
    if( n>db->lookaside.sz ){
      db->lookaside.anStat[1]++;
    }else if( (pBuf = db->lookaside.pFree)!=0 ){
      db->lookaside.pFree = pBuf->pNext;
      db->lookaside.anStat[0]++;
      return (void*)pBuf;
    }else if( (pBuf = db->lookaside.pInit)!=0 ){
      db->lookaside.pInit = pBuf->pNext;
      db->lookaside.anStat[0]++;
      return (void*)pBuf;
    }else{
      db->lookaside.anStat[2]++;
    }
  }else if( db->mallocFailed ){
    return 0;
  }
#else
  assert( db!=0 );
  assert( sqlite3_mutex_held(db->mutex) );
  assert( db->pnBytesFreed==0 );
  if( db->mallocFailed ){
    return 0;
  }
#endif
  return dbMallocRawFinish(db, n);
}