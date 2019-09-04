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
typedef  scalar_t__ int64 ;
struct TYPE_4__ {scalar_t__ lowest_modified_value; int /*<<< orphan*/  hypertable_relid; } ;
typedef  TYPE_1__ ContinuousAggsCacheInvalEntry ;

/* Variables and functions */
 scalar_t__ IsolationUsesXactSnapshot () ; 
 int /*<<< orphan*/  append_invalidation_entry (TYPE_1__*) ; 
 scalar_t__ get_lowest_invalidated_time_for_hypertable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cache_inval_entry_write(ContinuousAggsCacheInvalEntry *entry)
{
	int64 liv;
	/* The materialization worker uses a READ COMMITTED isolation level by default. Therefore, if we
	 * use a stronger isolation level, the isolation thereshold could update without us seeing the
	 * new value. In order to prevent serialization errors, we always append invalidation entires in
	 * the case when we're using a strong enough isolation level that we won't see the new
	 * threshold; the materializer can handle invalidations that are beyond the threshold
	 * gracefully.
	 */
	if (IsolationUsesXactSnapshot())
	{
		append_invalidation_entry(entry);
		return;
	}

	liv = get_lowest_invalidated_time_for_hypertable(entry->hypertable_relid);
	if (entry->lowest_modified_value < liv)
		append_invalidation_entry(entry);
}