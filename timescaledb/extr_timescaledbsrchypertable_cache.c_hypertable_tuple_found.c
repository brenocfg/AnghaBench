#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleInfo ;
struct TYPE_2__ {int /*<<< orphan*/  hypertable; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  TYPE_1__ HypertableCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/  ts_hypertable_from_tupleinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ScanTupleResult
hypertable_tuple_found(TupleInfo *ti, void *data)
{
	HypertableCacheEntry *entry = data;

	entry->hypertable = ts_hypertable_from_tupleinfo(ti);
	return SCAN_DONE;
}