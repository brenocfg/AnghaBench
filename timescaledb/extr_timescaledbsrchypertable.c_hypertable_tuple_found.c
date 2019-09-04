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
typedef  int /*<<< orphan*/  TupleInfo ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_DONE ; 
 int /*<<< orphan*/ * ts_hypertable_from_tupleinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ScanTupleResult
hypertable_tuple_found(TupleInfo *ti, void *data)
{
	Hypertable **entry = data;

	*entry = ts_hypertable_from_tupleinfo(ti);
	return SCAN_DONE;
}