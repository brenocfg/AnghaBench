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
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  bgw_job_stat_insert_mark_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgw_job_stat_scan_job_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgw_job_stat_tuple_mark_start ; 

void
ts_bgw_job_stat_mark_start(int32 bgw_job_id)
{
	if (!bgw_job_stat_scan_job_id(bgw_job_id,
								  bgw_job_stat_tuple_mark_start,
								  NULL,
								  NULL,
								  RowExclusiveLock))
		bgw_job_stat_insert_mark_start(bgw_job_id);
}