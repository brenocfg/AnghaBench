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
struct TYPE_3__ {int empty; int has_null; scalar_t__ max; scalar_t__ min; int /*<<< orphan*/  type_by_val; } ;
typedef  TYPE_1__ SegmentMetaMinMaxBuilder ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (scalar_t__) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

void
segment_meta_min_max_builder_reset(SegmentMetaMinMaxBuilder *builder)
{
	if (!builder->empty)
	{
		if (!builder->type_by_val)
		{
			pfree(DatumGetPointer(builder->min));
			pfree(DatumGetPointer(builder->max));
		}
		builder->min = 0;
		builder->max = 0;
	}
	builder->empty = true;
	builder->has_null = false;
}