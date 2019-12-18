#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct TYPE_6__ {int alarmThreshold; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int (* xRoundup ) (int) ;void* (* xRealloc ) (void*,int) ;} ;
struct TYPE_5__ {TYPE_1__ m; scalar_t__ bMemstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIGHT_BYTE_ALIGNMENT (void*) ; 
 scalar_t__ MEMTYPE_HEAP ; 
 int /*<<< orphan*/  SQLITE_STATUS_MALLOC_SIZE ; 
 int /*<<< orphan*/  SQLITE_STATUS_MEMORY_USED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__ mem0 ; 
 TYPE_2__ sqlite3GlobalConfig ; 
 void* sqlite3Malloc (int) ; 
 int /*<<< orphan*/  sqlite3MallocAlarm (int) ; 
 int sqlite3MallocSize (void*) ; 
 int /*<<< orphan*/  sqlite3MemdebugHasType (void*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3MemdebugNoType (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3StatusHighwater (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3StatusUp (int /*<<< orphan*/ ,int) ; 
 int sqlite3StatusValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int stub1 (int) ; 
 void* stub2 (void*,int) ; 
 void* stub3 (void*,int) ; 
 void* stub4 (void*,int) ; 

void *sqlite3Realloc(void *pOld, u64 nBytes){
  int nOld, nNew, nDiff;
  void *pNew;
  assert( sqlite3MemdebugHasType(pOld, MEMTYPE_HEAP) );
  assert( sqlite3MemdebugNoType(pOld, (u8)~MEMTYPE_HEAP) );
  if( pOld==0 ){
    return sqlite3Malloc(nBytes); /* IMP: R-04300-56712 */
  }
  if( nBytes==0 ){
    sqlite3_free(pOld); /* IMP: R-26507-47431 */
    return 0;
  }
  if( nBytes>=0x7fffff00 ){
    /* The 0x7ffff00 limit term is explained in comments on sqlite3Malloc() */
    return 0;
  }
  nOld = sqlite3MallocSize(pOld);
  /* IMPLEMENTATION-OF: R-46199-30249 SQLite guarantees that the second
  ** argument to xRealloc is always a value returned by a prior call to
  ** xRoundup. */
  nNew = sqlite3GlobalConfig.m.xRoundup((int)nBytes);
  if( nOld==nNew ){
    pNew = pOld;
  }else if( sqlite3GlobalConfig.bMemstat ){
    sqlite3_mutex_enter(mem0.mutex);
    sqlite3StatusHighwater(SQLITE_STATUS_MALLOC_SIZE, (int)nBytes);
    nDiff = nNew - nOld;
    if( nDiff>0 && sqlite3StatusValue(SQLITE_STATUS_MEMORY_USED) >= 
          mem0.alarmThreshold-nDiff ){
      sqlite3MallocAlarm(nDiff);
    }
    pNew = sqlite3GlobalConfig.m.xRealloc(pOld, nNew);
    if( pNew==0 && mem0.alarmThreshold>0 ){
      sqlite3MallocAlarm((int)nBytes);
      pNew = sqlite3GlobalConfig.m.xRealloc(pOld, nNew);
    }
    if( pNew ){
      nNew = sqlite3MallocSize(pNew);
      sqlite3StatusUp(SQLITE_STATUS_MEMORY_USED, nNew-nOld);
    }
    sqlite3_mutex_leave(mem0.mutex);
  }else{
    pNew = sqlite3GlobalConfig.m.xRealloc(pOld, nNew);
  }
  assert( EIGHT_BYTE_ALIGNMENT(pNew) ); /* IMP: R-11148-40995 */
  return pNew;
}