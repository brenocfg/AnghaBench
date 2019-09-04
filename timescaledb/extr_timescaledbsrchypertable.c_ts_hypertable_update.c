#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__ Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_hypertable_pkey_idx_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  HYPERTABLE_ID_INDEX ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hypertable_scan_limit_internal (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypertable_tuple_update ; 

int
ts_hypertable_update(Hypertable *ht)
{
	ScanKeyData scankey[1];

	ScanKeyInit(&scankey[0],
				Anum_hypertable_pkey_idx_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(ht->fd.id));

	return hypertable_scan_limit_internal(scankey,
										  1,
										  HYPERTABLE_ID_INDEX,
										  hypertable_tuple_update,
										  ht,
										  1,
										  RowExclusiveLock,
										  false,
										  CurrentMemoryContext);
}