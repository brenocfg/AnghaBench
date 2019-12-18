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
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  BgwPolicyReorder ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_bgw_policy_reorder_pkey_idx_job_id ; 
 int /*<<< orphan*/  BGW_POLICY_REORDER ; 
 int /*<<< orphan*/  BGW_POLICY_REORDER_PKEY_IDX ; 
 int /*<<< orphan*/  BGW_POLICY_REORDER_TABLE_NAME ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgw_policy_reorder_tuple_found ; 
 int /*<<< orphan*/  ts_catalog_scan_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

BgwPolicyReorder *
ts_bgw_policy_reorder_find_by_job(int32 job_id)
{
	ScanKeyData scankey[1];
	BgwPolicyReorder *ret = NULL;

	ScanKeyInit(&scankey[0],
				Anum_bgw_policy_reorder_pkey_idx_job_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(job_id));

	ts_catalog_scan_one(BGW_POLICY_REORDER,
						BGW_POLICY_REORDER_PKEY_IDX,
						scankey,
						1,
						bgw_policy_reorder_tuple_found,
						AccessShareLock,
						BGW_POLICY_REORDER_TABLE_NAME,
						(void *) &ret);

	return ret;
}