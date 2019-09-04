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
 int /*<<< orphan*/  Anum_bgw_policy_chunk_stats_chunk_id ; 
 int /*<<< orphan*/  BGW_POLICY_CHUNK_STATS ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgw_policy_chunk_stats_delete_via_job_tuple_found ; 
 int /*<<< orphan*/  ts_catalog_scan_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ts_bgw_policy_chunk_stats_delete_by_chunk_id(int32 chunk_id)
{
	ScanKeyData scankey[1];

	ScanKeyInit(&scankey[0],
				Anum_bgw_policy_chunk_stats_chunk_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(chunk_id));

	ts_catalog_scan_all(BGW_POLICY_CHUNK_STATS,
						InvalidOid,
						scankey,
						1,
						bgw_policy_chunk_stats_delete_via_job_tuple_found,
						RowExclusiveLock,
						NULL);
}