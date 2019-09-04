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
#define  SUBXACT_EVENT_ABORT_SUB 128 
 int /*<<< orphan*/  cache_invalidate_all () ; 

__attribute__((used)) static void
cache_invalidate_subxact_end(SubXactEvent event, SubTransactionId mySubid,
							 SubTransactionId parentSubid, void *arg)
{
	switch (event)
	{
		case SUBXACT_EVENT_ABORT_SUB:

			/*
			 * Invalidate caches on aborted sub transactions. See notes above
			 * in cache_invalidate_xact_end.
			 */
			cache_invalidate_all();
		default:
			break;
	}
}