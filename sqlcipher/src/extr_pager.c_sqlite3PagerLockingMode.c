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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ exclusiveMode; int /*<<< orphan*/  pWal; int /*<<< orphan*/  tempFile; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int PAGER_LOCKINGMODE_EXCLUSIVE ; 
 int PAGER_LOCKINGMODE_NORMAL ; 
 int PAGER_LOCKINGMODE_QUERY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3WalHeapMemory (int /*<<< orphan*/ ) ; 

int sqlite3PagerLockingMode(Pager *pPager, int eMode){
  assert( eMode==PAGER_LOCKINGMODE_QUERY
            || eMode==PAGER_LOCKINGMODE_NORMAL
            || eMode==PAGER_LOCKINGMODE_EXCLUSIVE );
  assert( PAGER_LOCKINGMODE_QUERY<0 );
  assert( PAGER_LOCKINGMODE_NORMAL>=0 && PAGER_LOCKINGMODE_EXCLUSIVE>=0 );
  assert( pPager->exclusiveMode || 0==sqlite3WalHeapMemory(pPager->pWal) );
  if( eMode>=0 && !pPager->tempFile && !sqlite3WalHeapMemory(pPager->pWal) ){
    pPager->exclusiveMode = (u8)eMode;
  }
  return (int)pPager->exclusiveMode;
}