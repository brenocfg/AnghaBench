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
struct TYPE_4__ {scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_1__ InternalTimeRange ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static bool
ranges_overlap(InternalTimeRange invalidation_range, InternalTimeRange new_materialization_range)
{
	Assert(invalidation_range.start <= invalidation_range.end);
	Assert(new_materialization_range.start <= new_materialization_range.end);
	return !(invalidation_range.end < new_materialization_range.start ||
			 new_materialization_range.end < invalidation_range.start);
}