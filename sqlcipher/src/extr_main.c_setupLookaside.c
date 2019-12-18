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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
typedef  int sqlite3_int64 ;
struct TYPE_7__ {int bMalloced; int nSlot; int bDisable; TYPE_2__* pEnd; TYPE_2__* pStart; TYPE_2__* pInit; scalar_t__ sz; scalar_t__ pFree; } ;
struct TYPE_8__ {TYPE_1__ lookaside; struct TYPE_8__* pNext; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  TYPE_2__ LookasideSlot ;

/* Variables and functions */
 int ROUNDDOWN8 (int) ; 
 int SQLITE_BUSY ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 scalar_t__ sqlite3LookasideUsed (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* sqlite3Malloc (int) ; 
 int sqlite3MallocSize (void*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static int setupLookaside(sqlite3 *db, void *pBuf, int sz, int cnt){
#ifndef SQLITE_OMIT_LOOKASIDE
  void *pStart;
  
  if( sqlite3LookasideUsed(db,0)>0 ){
    return SQLITE_BUSY;
  }
  /* Free any existing lookaside buffer for this handle before
  ** allocating a new one so we don't have to have space for 
  ** both at the same time.
  */
  if( db->lookaside.bMalloced ){
    sqlite3_free(db->lookaside.pStart);
  }
  /* The size of a lookaside slot after ROUNDDOWN8 needs to be larger
  ** than a pointer to be useful.
  */
  sz = ROUNDDOWN8(sz);  /* IMP: R-33038-09382 */
  if( sz<=(int)sizeof(LookasideSlot*) ) sz = 0;
  if( cnt<0 ) cnt = 0;
  if( sz==0 || cnt==0 ){
    sz = 0;
    pStart = 0;
  }else if( pBuf==0 ){
    sqlite3BeginBenignMalloc();
    pStart = sqlite3Malloc( sz*(sqlite3_int64)cnt );  /* IMP: R-61949-35727 */
    sqlite3EndBenignMalloc();
    if( pStart ) cnt = sqlite3MallocSize(pStart)/sz;
  }else{
    pStart = pBuf;
  }
  db->lookaside.pStart = pStart;
  db->lookaside.pInit = 0;
  db->lookaside.pFree = 0;
  db->lookaside.sz = (u16)sz;
  if( pStart ){
    int i;
    LookasideSlot *p;
    assert( sz > (int)sizeof(LookasideSlot*) );
    db->lookaside.nSlot = cnt;
    p = (LookasideSlot*)pStart;
    for(i=cnt-1; i>=0; i--){
      p->pNext = db->lookaside.pInit;
      db->lookaside.pInit = p;
      p = (LookasideSlot*)&((u8*)p)[sz];
    }
    db->lookaside.pEnd = p;
    db->lookaside.bDisable = 0;
    db->lookaside.bMalloced = pBuf==0 ?1:0;
  }else{
    db->lookaside.pStart = db;
    db->lookaside.pEnd = db;
    db->lookaside.bDisable = 1;
    db->lookaside.bMalloced = 0;
    db->lookaside.nSlot = 0;
  }
#endif /* SQLITE_OMIT_LOOKASIDE */
  return SQLITE_OK;
}