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
typedef  int /*<<< orphan*/  ScanKeyData ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_continuous_aggs_invalidation_threshold_pkey_hypertable_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CONTINUOUS_AGGS_INVALIDATION_THRESHOLD ; 
 int /*<<< orphan*/  CONTINUOUS_AGGS_INVALIDATION_THRESHOLD_PKEY ; 
 int /*<<< orphan*/  CONTINUOUS_AGGS_INVALIDATION_THRESHOLD_TABLE_NAME ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidation_threshold_tuple_found ; 
 int /*<<< orphan*/  ts_catalog_scan_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int64
invalidation_threshold_get(int32 hypertable_id)
{
	int64 threshold = 0;
	ScanKeyData scankey[1];

	ScanKeyInit(&scankey[0],
				Anum_continuous_aggs_invalidation_threshold_pkey_hypertable_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(hypertable_id));

	if (!ts_catalog_scan_one(CONTINUOUS_AGGS_INVALIDATION_THRESHOLD /*=table*/,
							 CONTINUOUS_AGGS_INVALIDATION_THRESHOLD_PKEY /*=indexid*/,
							 scankey /*=scankey*/,
							 1 /*=num_keys*/,
							 invalidation_threshold_tuple_found /*=tuple_found*/,
							 AccessShareLock /*=lockmode*/,
							 CONTINUOUS_AGGS_INVALIDATION_THRESHOLD_TABLE_NAME /*=table_name*/,
							 &threshold /*=data*/))
		elog(ERROR, "could not find invalidation threshold for hypertable %d", hypertable_id);

	return threshold;
}