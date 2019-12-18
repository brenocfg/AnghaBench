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
struct TYPE_3__ {int empty; int /*<<< orphan*/  type_len; int /*<<< orphan*/  type_by_val; void* max; int /*<<< orphan*/  ssup; void* min; } ;
typedef  TYPE_1__ SegmentMetaMinMaxBuilder ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int ApplySortComparator (void*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DatumGetPointer (void*) ; 
 void* datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

void
segment_meta_min_max_builder_update_val(SegmentMetaMinMaxBuilder *builder, Datum val)
{
	int cmp;

	if (builder->empty)
	{
		builder->min = datumCopy(val, builder->type_by_val, builder->type_len);
		builder->max = datumCopy(val, builder->type_by_val, builder->type_len);
		builder->empty = false;
		return;
	}

	cmp = ApplySortComparator(builder->min, false, val, false, &builder->ssup);
	if (cmp > 0)
	{
		if (!builder->type_by_val)
			pfree(DatumGetPointer(builder->min));
		builder->min = datumCopy(val, builder->type_by_val, builder->type_len);
	}

	cmp = ApplySortComparator(builder->max, false, val, false, &builder->ssup);
	if (cmp < 0)
	{
		if (!builder->type_by_val)
			pfree(DatumGetPointer(builder->max));
		builder->max = datumCopy(val, builder->type_by_val, builder->type_len);
	}
}