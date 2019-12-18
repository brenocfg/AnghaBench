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
struct TYPE_3__ {int /*<<< orphan*/  desc; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/  DimensionType ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_dimension_interval_length ; 
 int /*<<< orphan*/  Anum_dimension_num_slices ; 
 int /*<<< orphan*/  DIMENSION_TYPE_ANY ; 
 int /*<<< orphan*/  DIMENSION_TYPE_CLOSED ; 
 int /*<<< orphan*/  DIMENSION_TYPE_OPEN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ heap_attisnull_compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline DimensionType
dimension_type(TupleInfo *ti)
{
	if (heap_attisnull_compat(ti->tuple, Anum_dimension_interval_length, ti->desc) &&
		!heap_attisnull_compat(ti->tuple, Anum_dimension_num_slices, ti->desc))
		return DIMENSION_TYPE_CLOSED;

	if (!heap_attisnull_compat(ti->tuple, Anum_dimension_interval_length, ti->desc) &&
		heap_attisnull_compat(ti->tuple, Anum_dimension_num_slices, ti->desc))
		return DIMENSION_TYPE_OPEN;

	elog(ERROR, "invalid partitioning dimension");
	/* suppress compiler warning on MSVC */
	return DIMENSION_TYPE_ANY;
}