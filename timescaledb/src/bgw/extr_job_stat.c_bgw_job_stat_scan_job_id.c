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
typedef  int /*<<< orphan*/  tuple_found_func ;
typedef  int /*<<< orphan*/  tuple_filter_func ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_bgw_job_stat_pkey_idx_job_id ; 
 int /*<<< orphan*/  BGW_JOB_STAT_PKEY_IDX ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bgw_job_stat_scan_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
bgw_job_stat_scan_job_id(int32 bgw_job_id, tuple_found_func tuple_found,
						 tuple_filter_func tuple_filter, void *data, LOCKMODE lockmode)
{
	ScanKeyData scankey[1];

	ScanKeyInit(&scankey[0],
				Anum_bgw_job_stat_pkey_idx_job_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(bgw_job_id));
	return bgw_job_stat_scan_one(BGW_JOB_STAT_PKEY_IDX,
								 scankey,
								 1,
								 tuple_found,
								 tuple_filter,
								 data,
								 lockmode);
}