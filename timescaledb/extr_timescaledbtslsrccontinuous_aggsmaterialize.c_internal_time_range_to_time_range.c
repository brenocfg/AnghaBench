#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* end; void* start; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ TimeRange ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_2__ InternalTimeRange ;

/* Variables and functions */
 void* internal_to_time_value_or_infinite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TimeRange
internal_time_range_to_time_range(InternalTimeRange internal)
{
	TimeRange range;
	range.type = internal.type;

	range.start = internal_to_time_value_or_infinite(internal.start, internal.type, NULL);
	range.end = internal_to_time_value_or_infinite(internal.end, internal.type, NULL);

	return range;
}