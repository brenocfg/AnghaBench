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
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ PG_INT64_MAX ; 
 scalar_t__ PG_INT64_MIN ; 
 int /*<<< orphan*/  time_range_internal_to_max_time_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_range_internal_to_min_time_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_internal_to_time_value (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
internal_to_time_value_or_infinite(int64 internal, Oid time_type, bool *is_infinite_out)
{
	/* MIN and MAX can occur due to NULL thresholds, or due to a lack of invalidations. Since our
	 * regular conversion function errors in those cases, and we want to use those as markers for an
	 * open threshold in one direction, we special case this here*/
	if (internal == PG_INT64_MIN)
	{
		if (is_infinite_out != NULL)
			*is_infinite_out = true;
		return time_range_internal_to_min_time_value(time_type);
	}
	else if (internal == PG_INT64_MAX)
	{
		if (is_infinite_out != NULL)
			*is_infinite_out = true;
		return time_range_internal_to_max_time_value(time_type);
	}
	else
	{
		if (is_infinite_out != NULL)
			*is_infinite_out = false;
		return ts_internal_to_time_value(internal, time_type);
	}
}