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

/* Variables and functions */
 int /*<<< orphan*/  Anum_bgw_policy_drop_chunks_pkey_job_id ; 
 int /*<<< orphan*/  BGW_POLICY_DROP_CHUNKS ; 
 int /*<<< orphan*/  BGW_POLICY_DROP_CHUNKS_PKEY ; 
 int /*<<< orphan*/  BGW_POLICY_DROP_CHUNKS_TABLE_NAME ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_policy_delete_row_only_tuple_found ; 
 int ts_catalog_scan_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
ts_bgw_policy_drop_chunks_delete_row_only_by_job_id(int32 job_id)
{
	ScanKeyData scankey[1];

	ScanKeyInit(&scankey[0],
				Anum_bgw_policy_drop_chunks_pkey_job_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(job_id));

	return ts_catalog_scan_one(BGW_POLICY_DROP_CHUNKS,
							   BGW_POLICY_DROP_CHUNKS_PKEY,
							   scankey,
							   1,
							   ts_bgw_policy_delete_row_only_tuple_found,
							   RowExclusiveLock,
							   BGW_POLICY_DROP_CHUNKS_TABLE_NAME,
							   NULL);
}