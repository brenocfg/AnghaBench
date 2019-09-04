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
struct TYPE_5__ {TYPE_1__* dimension; } ;
struct TYPE_4__ {int type; } ;
typedef  int /*<<< orphan*/  DimensionVec ;
typedef  int /*<<< orphan*/  DimensionRestrictInfoOpen ;
typedef  int /*<<< orphan*/  DimensionRestrictInfoClosed ;
typedef  TYPE_2__ DimensionRestrictInfo ;

/* Variables and functions */
#define  DIMENSION_TYPE_CLOSED 129 
#define  DIMENSION_TYPE_OPEN 128 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * dimension_restrict_info_closed_slices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dimension_restrict_info_open_slices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static DimensionVec *
dimension_restrict_info_slices(DimensionRestrictInfo *dri)
{
	switch (dri->dimension->type)
	{
		case DIMENSION_TYPE_OPEN:
			return dimension_restrict_info_open_slices((DimensionRestrictInfoOpen *) dri);
		case DIMENSION_TYPE_CLOSED:
			return dimension_restrict_info_closed_slices((DimensionRestrictInfoClosed *) dri);
		default:
			elog(ERROR, "unknown dimension type");
			return NULL;
	}
}