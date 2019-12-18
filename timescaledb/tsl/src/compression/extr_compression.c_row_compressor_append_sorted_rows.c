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
typedef  int /*<<< orphan*/  Tuplesortstate ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_7__ {scalar_t__ rows_compressed_into_current_value; int /*<<< orphan*/  per_row_ctx; } ;
typedef  TYPE_1__ RowCompressor ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  CommandId ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentCommandId (int) ; 
 scalar_t__ MAX_ROWS_PER_COMPRESSION ; 
 int /*<<< orphan*/ * MakeTupleTableSlotCompat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  row_compressor_append_row (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  row_compressor_flush (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int row_compressor_new_row_is_in_new_group (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  row_compressor_update_group (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_getallattrs (int /*<<< orphan*/ *) ; 
 int tuplesort_gettupleslot (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
row_compressor_append_sorted_rows(RowCompressor *row_compressor, Tuplesortstate *sorted_rel,
								  TupleDesc sorted_desc)
{
	CommandId mycid = GetCurrentCommandId(true);
	TupleTableSlot *slot = MakeTupleTableSlotCompat(sorted_desc);
	bool got_tuple;
	bool first_iteration = true;

	for (got_tuple = tuplesort_gettupleslot(sorted_rel,
											true /*=forward*/,
#if !PG96
											false /*=copy*/,
#endif
											slot,
											NULL /*=abbrev*/);
		 got_tuple;
		 got_tuple = tuplesort_gettupleslot(sorted_rel,
											true /*=forward*/,
#if !PG96
											false /*=copy*/,
#endif
											slot,
											NULL /*=abbrev*/))
	{
		bool changed_groups, compressed_row_is_full;
		MemoryContext old_ctx;
		slot_getallattrs(slot);
		old_ctx = MemoryContextSwitchTo(row_compressor->per_row_ctx);

		/* first time through */
		if (first_iteration)
		{
			row_compressor_update_group(row_compressor, slot);
			first_iteration = false;
		}

		changed_groups = row_compressor_new_row_is_in_new_group(row_compressor, slot);
		compressed_row_is_full =
			row_compressor->rows_compressed_into_current_value >= MAX_ROWS_PER_COMPRESSION;
		if (compressed_row_is_full || changed_groups)
		{
			if (row_compressor->rows_compressed_into_current_value > 0)
				row_compressor_flush(row_compressor, mycid, changed_groups);
			if (changed_groups)
				row_compressor_update_group(row_compressor, slot);
		}

		row_compressor_append_row(row_compressor, slot);
		MemoryContextSwitchTo(old_ctx);
		ExecClearTuple(slot);
	}

	if (row_compressor->rows_compressed_into_current_value > 0)
		row_compressor_flush(row_compressor, mycid, true);

	ExecDropSingleTupleTableSlot(slot);
}