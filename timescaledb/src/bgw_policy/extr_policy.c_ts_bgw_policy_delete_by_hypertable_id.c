#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_6__ {int /*<<< orphan*/  job_id; } ;
struct TYPE_8__ {TYPE_2__ fd; } ;
struct TYPE_5__ {int /*<<< orphan*/  job_id; } ;
struct TYPE_7__ {TYPE_1__ fd; } ;
typedef  TYPE_3__ BgwPolicyReorder ;
typedef  TYPE_4__ BgwPolicyDropChunks ;

/* Variables and functions */
 int /*<<< orphan*/  ts_bgw_job_delete_by_id (int /*<<< orphan*/ ) ; 
 void* ts_bgw_policy_drop_chunks_find_by_hypertable (int /*<<< orphan*/ ) ; 
 void* ts_bgw_policy_reorder_find_by_hypertable (int /*<<< orphan*/ ) ; 

void
ts_bgw_policy_delete_by_hypertable_id(int32 hypertable_id)
{
	/*
	 * Because this is used in a cascaded delete from hypertable deletion, we
	 * also need to delete the job. This means we don't actually call the
	 * delete on the individual policy, but call the bgw_job delete function.
	 */
	void *policy = ts_bgw_policy_reorder_find_by_hypertable(hypertable_id);

	if (policy)
		ts_bgw_job_delete_by_id(((BgwPolicyReorder *) policy)->fd.job_id);

	policy = ts_bgw_policy_drop_chunks_find_by_hypertable(hypertable_id);

	if (policy)
		ts_bgw_job_delete_by_id(((BgwPolicyDropChunks *) policy)->fd.job_id);
}