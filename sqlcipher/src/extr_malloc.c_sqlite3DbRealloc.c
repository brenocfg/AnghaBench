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
typedef  scalar_t__ u64 ;
struct TYPE_7__ {scalar_t__ sz; } ;
struct TYPE_8__ {TYPE_1__ lookaside; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* dbReallocFinish (TYPE_2__*,void*,scalar_t__) ; 
 scalar_t__ isLookaside (TYPE_2__*,void*) ; 
 void* sqlite3DbMallocRawNN (TYPE_2__*,scalar_t__) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void *sqlite3DbRealloc(sqlite3 *db, void *p, u64 n){
  assert( db!=0 );
  if( p==0 ) return sqlite3DbMallocRawNN(db, n);
  assert( sqlite3_mutex_held(db->mutex) );
  if( isLookaside(db,p) && n<=db->lookaside.sz ) return p;
  return dbReallocFinish(db, p, n);
}