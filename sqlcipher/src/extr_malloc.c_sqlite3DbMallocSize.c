#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int sz; } ;
struct TYPE_9__ {TYPE_2__ lookaside; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_7__ {int (* xSize ) (void*) ;} ;
struct TYPE_10__ {TYPE_1__ m; } ;

/* Variables and functions */
 int MEMTYPE_HEAP ; 
 int MEMTYPE_LOOKASIDE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isLookaside (TYPE_3__*,void*) ; 
 TYPE_4__ sqlite3GlobalConfig ; 
 int sqlite3MemdebugHasType (void*,int) ; 
 int sqlite3MemdebugNoType (void*,int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int stub1 (void*) ; 

int sqlite3DbMallocSize(sqlite3 *db, void *p){
  assert( p!=0 );
  if( db==0 || !isLookaside(db,p) ){
#ifdef SQLITE_DEBUG
    if( db==0 ){
      assert( sqlite3MemdebugNoType(p, (u8)~MEMTYPE_HEAP) );
      assert( sqlite3MemdebugHasType(p, MEMTYPE_HEAP) );
    }else{
      assert( sqlite3MemdebugHasType(p, (MEMTYPE_LOOKASIDE|MEMTYPE_HEAP)) );
      assert( sqlite3MemdebugNoType(p, (u8)~(MEMTYPE_LOOKASIDE|MEMTYPE_HEAP)) );
    }
#endif
    return sqlite3GlobalConfig.m.xSize(p);
  }else{
    assert( sqlite3_mutex_held(db->mutex) );
    return db->lookaside.sz;
  }
}