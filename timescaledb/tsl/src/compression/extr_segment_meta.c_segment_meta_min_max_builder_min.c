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
struct TYPE_3__ {int type_len; scalar_t__ min; scalar_t__ empty; } ;
typedef  TYPE_1__ SegmentMetaMinMaxBuilder ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_DETOAST_DATUM_PACKED (scalar_t__) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

Datum
segment_meta_min_max_builder_min(SegmentMetaMinMaxBuilder *builder)
{
	if (builder->empty)
		elog(ERROR, "trying to get min from an empty builder");
	if (builder->type_len == -1)
	{
		Datum unpacked = PointerGetDatum(PG_DETOAST_DATUM_PACKED(builder->min));
		if (builder->min != unpacked)
			pfree(DatumGetPointer(builder->min));
		builder->min = unpacked;
	}
	return builder->min;
}