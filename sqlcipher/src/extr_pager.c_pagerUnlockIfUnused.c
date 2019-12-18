#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nMmapOut; int /*<<< orphan*/  pPCache; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pagerUnlockAndRollback (TYPE_1__*) ; 
 scalar_t__ sqlite3PcacheRefCount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pagerUnlockIfUnused(Pager *pPager){
  if( sqlite3PcacheRefCount(pPager->pPCache)==0 ){
    assert( pPager->nMmapOut==0 ); /* because page1 is never memory mapped */
    pagerUnlockAndRollback(pPager);
  }
}