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
struct TYPE_4__ {int pgno; int flags; int /*<<< orphan*/ * pPager; } ;
typedef  int /*<<< orphan*/  Pager ;
typedef  TYPE_1__ DbPage ;

/* Variables and functions */
 int PGHDR_MMAP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pagerUnlockIfUnused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3PagerResetLockTimeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3PcacheRelease (TYPE_1__*) ; 

void sqlite3PagerUnrefPageOne(DbPage *pPg){
  Pager *pPager;
  assert( pPg!=0 );
  assert( pPg->pgno==1 );
  assert( (pPg->flags & PGHDR_MMAP)==0 ); /* Page1 is never memory mapped */
  pPager = pPg->pPager;
  sqlite3PagerResetLockTimeout(pPager);
  sqlite3PcacheRelease(pPg);
  pagerUnlockIfUnused(pPager);
}