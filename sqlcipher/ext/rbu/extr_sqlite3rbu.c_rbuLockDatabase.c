#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ rc; TYPE_1__* pTargetFd; } ;
typedef  TYPE_3__ sqlite3rbu ;
struct TYPE_11__ {TYPE_2__* pMethods; } ;
typedef  TYPE_4__ sqlite3_file ;
struct TYPE_9__ {scalar_t__ (* xLock ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_4__* pReal; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  SQLITE_LOCK_SHARED ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbuLockDatabase(sqlite3rbu *p){
  sqlite3_file *pReal = p->pTargetFd->pReal;
  assert( p->rc==SQLITE_OK );
  p->rc = pReal->pMethods->xLock(pReal, SQLITE_LOCK_SHARED);
  if( p->rc==SQLITE_OK ){
    p->rc = pReal->pMethods->xLock(pReal, SQLITE_LOCK_EXCLUSIVE);
  }
}