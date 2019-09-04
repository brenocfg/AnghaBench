#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_4__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_5__ {scalar_t__ watermark; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  TYPE_2__* Form_continuous_aggs_invalidation_threshold ;

/* Variables and functions */
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 

__attribute__((used)) static ScanTupleResult
invalidation_tuple_found(TupleInfo *ti, void *min)
{
	Form_continuous_aggs_invalidation_threshold invalidation =
		(Form_continuous_aggs_invalidation_threshold) GETSTRUCT(ti->tuple);
	if (invalidation->watermark < *(int64 *) min)
		*(int64 *) min = invalidation->watermark;

	/*
	 * Return SCAN_CONTINUE because we check for multiple tuples as an error
	 * condition.
	 */
	return SCAN_CONTINUE;
}