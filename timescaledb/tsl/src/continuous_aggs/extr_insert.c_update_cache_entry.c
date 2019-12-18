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
typedef  scalar_t__ int64 ;
struct TYPE_3__ {scalar_t__ lowest_modified_value; scalar_t__ greatest_modified_value; } ;
typedef  TYPE_1__ ContinuousAggsCacheInvalEntry ;

/* Variables and functions */

__attribute__((used)) static inline void
update_cache_entry(ContinuousAggsCacheInvalEntry *cache_entry, int64 timeval)
{
	if (timeval < cache_entry->lowest_modified_value)
		cache_entry->lowest_modified_value = timeval;
	if (timeval > cache_entry->greatest_modified_value)
		cache_entry->greatest_modified_value = timeval;
}