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
#define  XACT_EVENT_ABORT 130 
#define  XACT_EVENT_PARALLEL_ABORT 129 
#define  XACT_EVENT_PRE_COMMIT 128 
 int /*<<< orphan*/  cache_inval_cleanup () ; 
 int /*<<< orphan*/  cache_inval_htab_write () ; 
 int /*<<< orphan*/  continuous_aggs_cache_inval_htab ; 

__attribute__((used)) static void
continuous_agg_xact_invalidation_callback(XactEvent event, void *arg)
{
	/* Return quickly if we never initialize the hashtable */
	if (!continuous_aggs_cache_inval_htab)
		return;

	switch (event)
	{
		case XACT_EVENT_PRE_COMMIT:
			cache_inval_htab_write();
			cache_inval_cleanup();
			break;
		case XACT_EVENT_ABORT:
		case XACT_EVENT_PARALLEL_ABORT:
			cache_inval_cleanup();
			break;
		default:
			break;
	}
}