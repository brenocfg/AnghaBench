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
typedef  int int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int /*<<< orphan*/  space; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Interval ;
typedef  TYPE_1__ Hypertable ;
typedef  int /*<<< orphan*/  Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DEFAULT_SCHEDULE_INTERVAL ; 
 int /*<<< orphan*/ * DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Float8GetDatum (int) ; 
 scalar_t__ IS_TIMESTAMP_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int USECS_PER_SEC ; 
 int /*<<< orphan*/ * hyperspace_get_open_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_interval ; 
 int /*<<< orphan*/  ts_dimension_get_partition_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* ts_hypertable_get_by_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Interval *
continuous_agg_job_get_default_schedule_interval(int32 raw_table_id, int64 bucket_width)
{
	Dimension *dim;
	Interval *default_schedule_interval = DEFAULT_SCHEDULE_INTERVAL;
	Hypertable *ht = ts_hypertable_get_by_id(raw_table_id);
	Oid partition_type;

	Assert(ht != NULL);

	/*
	 * Try to see if the hypertable has a specified chunk length for the
	 * default schedule interval
	 */
	dim = hyperspace_get_open_dimension(ht->space, 0);

	partition_type = ts_dimension_get_partition_type(dim);
	if (dim != NULL && IS_TIMESTAMP_TYPE(partition_type))
	{
		default_schedule_interval = DatumGetIntervalP(
			DirectFunctionCall7(make_interval,
								Int32GetDatum(0),
								Int32GetDatum(0),
								Int32GetDatum(0),
								Int32GetDatum(0),
								Int32GetDatum(0),
								Int32GetDatum(0),
								Float8GetDatum((bucket_width * 2) / USECS_PER_SEC)));
	}

	return default_schedule_interval;
}