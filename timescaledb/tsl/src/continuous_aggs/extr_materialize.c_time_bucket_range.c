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
struct TYPE_3__ {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ InternalTimeRange ;

/* Variables and functions */
 scalar_t__ PG_INT64_MAX ; 
 void* ts_time_bucket_by_type (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
time_bucket_range(InternalTimeRange *range, int64 bucket_width)
{
	range->start = ts_time_bucket_by_type(bucket_width, range->start, range->type);
	range->end = ts_time_bucket_by_type(bucket_width, range->end, range->type);

	if (range->end < PG_INT64_MAX - bucket_width)
		range->end += bucket_width;

	if (range->start > range->end)
		range->start = range->end;
}