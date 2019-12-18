#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lockresult; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  HTSU_Result ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_DONE ; 

__attribute__((used)) static ScanTupleResult
tuple_found_lock(TupleInfo *ti, void *data)
{
	HTSU_Result *result = data;

	*result = ti->lockresult;
	return SCAN_DONE;
}