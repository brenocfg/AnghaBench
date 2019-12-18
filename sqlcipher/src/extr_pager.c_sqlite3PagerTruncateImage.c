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
struct TYPE_3__ {scalar_t__ dbSize; scalar_t__ eState; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_WRITER_CACHEMOD ; 
 int /*<<< orphan*/  assert (int) ; 

void sqlite3PagerTruncateImage(Pager *pPager, Pgno nPage){
  assert( pPager->dbSize>=nPage );
  assert( pPager->eState>=PAGER_WRITER_CACHEMOD );
  pPager->dbSize = nPage;

  /* At one point the code here called assertTruncateConstraint() to
  ** ensure that all pages being truncated away by this operation are,
  ** if one or more savepoints are open, present in the savepoint 
  ** journal so that they can be restored if the savepoint is rolled
  ** back. This is no longer necessary as this function is now only
  ** called right before committing a transaction. So although the 
  ** Pager object may still have open savepoints (Pager.nSavepoint!=0), 
  ** they cannot be rolled back. So the assertTruncateConstraint() call
  ** is no longer correct. */
}