#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* dimension; } ;
struct TYPE_9__ {int /*<<< orphan*/  lower_bound; int /*<<< orphan*/  lower_strategy; int /*<<< orphan*/  upper_bound; int /*<<< orphan*/  upper_strategy; TYPE_3__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  DimensionVec ;
typedef  TYPE_4__ DimensionRestrictInfoOpen ;

/* Variables and functions */
 int /*<<< orphan*/ * ts_dimension_slice_scan_range_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DimensionVec *
dimension_restrict_info_open_slices(DimensionRestrictInfoOpen *dri)
{
	/* basic idea: slice_end > lower_bound && slice_start < upper_bound */
	return ts_dimension_slice_scan_range_limit(dri->base.dimension->fd.id,
											   dri->upper_strategy,
											   dri->upper_bound,
											   dri->lower_strategy,
											   dri->lower_bound,
											   0);
}