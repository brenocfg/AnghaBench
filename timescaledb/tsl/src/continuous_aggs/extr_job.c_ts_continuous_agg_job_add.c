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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  Interval ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MAX_RETRIES ; 
 int /*<<< orphan*/  DEFAULT_MAX_RUNTIME ; 
 int /*<<< orphan*/ * continuous_agg_job_get_default_schedule_interval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ts_bgw_job_insert_relation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int32
ts_continuous_agg_job_add(int32 raw_table_id, int64 bucket_width, Interval *refresh_interval)
{
	NameData application_name;
	NameData job_type;
	int32 job_id;

	namestrcpy(&job_type, "continuous_aggregate");
	namestrcpy(&application_name, "Continuous Aggregate Background Job");

	if (refresh_interval == NULL)
		refresh_interval =
			continuous_agg_job_get_default_schedule_interval(raw_table_id, bucket_width);

	job_id = ts_bgw_job_insert_relation(&application_name,
										&job_type,
										refresh_interval,
										DEFAULT_MAX_RUNTIME,
										DEFAULT_MAX_RETRIES,
										refresh_interval);
	return job_id;
}