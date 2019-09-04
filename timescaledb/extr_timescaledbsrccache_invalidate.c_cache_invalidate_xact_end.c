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
typedef  int XactEvent ;

/* Variables and functions */
#define  XACT_EVENT_ABORT 129 
#define  XACT_EVENT_PARALLEL_ABORT 128 
 int /*<<< orphan*/  cache_invalidate_all () ; 

__attribute__((used)) static void
cache_invalidate_xact_end(XactEvent event, void *arg)
{
	switch (event)
	{
		case XACT_EVENT_ABORT:
		case XACT_EVENT_PARALLEL_ABORT:

			/*
			 * Invalidate caches on aborted transactions to purge entries that
			 * have been added during the transaction and are now no longer
			 * valid. Note that we need not signal other backends of this
			 * change since the transaction hasn't been committed and other
			 * backends cannot have the invalid state.
			 */
			cache_invalidate_all();
		default:
			break;
	}
}