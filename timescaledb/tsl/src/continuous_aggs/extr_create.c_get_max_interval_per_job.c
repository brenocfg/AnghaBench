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
typedef  int int64 ;
struct TYPE_4__ {scalar_t__ is_default; } ;
typedef  TYPE_1__ WithClauseResult ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 size_t ContinuousViewOptionMaxIntervalPerRun ; 
 int DEFAULT_MAX_INTERVAL_MAX_BUCKET_WIDTH ; 
 int DEFAULT_MAX_INTERVAL_MULTIPLIER ; 
 int PG_INT64_MAX ; 
 int continuous_agg_parse_max_interval_per_job (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int64
get_max_interval_per_job(Oid column_type, WithClauseResult *with_clause_options, int64 bucket_width)
{
	if (with_clause_options[ContinuousViewOptionMaxIntervalPerRun].is_default)
	{
		return (bucket_width < DEFAULT_MAX_INTERVAL_MAX_BUCKET_WIDTH) ?
				   DEFAULT_MAX_INTERVAL_MULTIPLIER * bucket_width :
				   PG_INT64_MAX;
	}
	return continuous_agg_parse_max_interval_per_job(column_type,
													 with_clause_options,
													 bucket_width);
}