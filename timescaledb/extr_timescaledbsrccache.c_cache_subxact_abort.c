#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int SubXactEvent ;
typedef  int /*<<< orphan*/  SubTransactionId ;

/* Variables and functions */
#define  SUBXACT_EVENT_ABORT_SUB 131 
#define  SUBXACT_EVENT_COMMIT_SUB 130 
#define  SUBXACT_EVENT_PRE_COMMIT_SUB 129 
#define  SUBXACT_EVENT_START_SUB 128 
 int /*<<< orphan*/  release_subtxn_pinned_caches (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cache_subxact_abort(SubXactEvent event, SubTransactionId subtxn_id, SubTransactionId parentSubid,
					void *arg)
{
	/*
	 * Note that cache->release_on_commit is irrelevant here since can't have
	 * cross-commit operations in subtxns
	 */
	/*
	 * In subtxns, caches should have already been released, unless an abort
	 * happened. Be careful to only release caches that were created in the
	 * same subtxn.
	 */

	switch (event)
	{
		case SUBXACT_EVENT_START_SUB:
		case SUBXACT_EVENT_PRE_COMMIT_SUB:
			/* do nothing */
			break;
		case SUBXACT_EVENT_COMMIT_SUB:
			release_subtxn_pinned_caches(subtxn_id, false);
			break;
		case SUBXACT_EVENT_ABORT_SUB:
			release_subtxn_pinned_caches(subtxn_id, true);
			break;
	}
}