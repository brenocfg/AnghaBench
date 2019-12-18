#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * storage_free; int /*<<< orphan*/ * storage; } ;
typedef  TYPE_1__ DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 TYPE_1__* palloc (int) ; 

DimensionSlice *
ts_dimension_slice_copy(const DimensionSlice *original)
{
	DimensionSlice *new = palloc(sizeof(DimensionSlice));

	Assert(original->storage == NULL);
	Assert(original->storage_free == NULL);

	memcpy(new, original, sizeof(DimensionSlice));
	return new;
}