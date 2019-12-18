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
struct TYPE_4__ {scalar_t__ eState; scalar_t__ journalOff; int /*<<< orphan*/  jfd; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 scalar_t__ PAGER_WRITER_CACHEMOD ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_pager_state (TYPE_1__*) ; 
 scalar_t__ isOpen (int /*<<< orphan*/ ) ; 

int sqlite3PagerOkToChangeJournalMode(Pager *pPager){
  assert( assert_pager_state(pPager) );
  if( pPager->eState>=PAGER_WRITER_CACHEMOD ) return 0;
  if( NEVER(isOpen(pPager->jfd) && pPager->journalOff>0) ) return 0;
  return 1;
}