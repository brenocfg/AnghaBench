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
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  bgw_job_scan_job_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bgw_job_tuple_found ; 

BgwJob *
ts_bgw_job_find(int32 bgw_job_id, MemoryContext mctx, bool fail_if_not_found)
{
	BgwJob *job_stat = NULL;

	bgw_job_scan_job_id(bgw_job_id,
						bgw_job_tuple_found,
						NULL,
						&job_stat,
						mctx,
						AccessShareLock,
						fail_if_not_found);

	return job_stat;
}