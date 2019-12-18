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
struct TYPE_8__ {TYPE_1__* db; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ Btree ;

/* Variables and functions */
 int /*<<< orphan*/  MASTER_ROOT ; 
 int /*<<< orphan*/  READ_LOCK ; 
 int SQLITE_LOCKED_SHAREDCACHE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int querySharedCacheTableLock (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_2__*) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

int sqlite3BtreeSchemaLocked(Btree *p){
  int rc;
  assert( sqlite3_mutex_held(p->db->mutex) );
  sqlite3BtreeEnter(p);
  rc = querySharedCacheTableLock(p, MASTER_ROOT, READ_LOCK);
  assert( rc==SQLITE_OK || rc==SQLITE_LOCKED_SHAREDCACHE );
  sqlite3BtreeLeave(p);
  return rc;
}