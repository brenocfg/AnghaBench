#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {TYPE_3__* pFree; int /*<<< orphan*/  sz; } ;
struct TYPE_8__ {TYPE_1__ lookaside; scalar_t__ pnBytesFreed; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_9__ {struct TYPE_9__* pNext; } ;
typedef  TYPE_3__ LookasideSlot ;

/* Variables and functions */
 int MEMTYPE_HEAP ; 
 int MEMTYPE_LOOKASIDE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isLookaside (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  measureAllocationSize (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  memset (void*,int,int /*<<< orphan*/ ) ; 
 int sqlite3MemdebugHasType (void*,int) ; 
 int sqlite3MemdebugNoType (void*,int) ; 
 int /*<<< orphan*/  sqlite3MemdebugSetType (void*,int) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3DbFreeNN(sqlite3 *db, void *p){
  assert( db==0 || sqlite3_mutex_held(db->mutex) );
  assert( p!=0 );
  if( db ){
    if( db->pnBytesFreed ){
      measureAllocationSize(db, p);
      return;
    }
    if( isLookaside(db, p) ){
      LookasideSlot *pBuf = (LookasideSlot*)p;
#ifdef SQLITE_DEBUG
      /* Trash all content in the buffer being freed */
      memset(p, 0xaa, db->lookaside.sz);
#endif
      pBuf->pNext = db->lookaside.pFree;
      db->lookaside.pFree = pBuf;
      return;
    }
  }
  assert( sqlite3MemdebugHasType(p, (MEMTYPE_LOOKASIDE|MEMTYPE_HEAP)) );
  assert( sqlite3MemdebugNoType(p, (u8)~(MEMTYPE_LOOKASIDE|MEMTYPE_HEAP)) );
  assert( db!=0 || sqlite3MemdebugNoType(p, MEMTYPE_LOOKASIDE) );
  sqlite3MemdebugSetType(p, MEMTYPE_HEAP);
  sqlite3_free(p);
}