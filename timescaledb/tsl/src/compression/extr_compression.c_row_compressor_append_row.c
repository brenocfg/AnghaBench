#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_9__ {int /*<<< orphan*/  (* append_val ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* append_null ) (TYPE_3__*) ;} ;
struct TYPE_8__ {int n_input_columns; int rows_compressed_into_current_value; TYPE_1__* per_column; } ;
struct TYPE_7__ {int /*<<< orphan*/ * min_max_metadata_builder; TYPE_3__* compressor; } ;
typedef  TYPE_2__ RowCompressor ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ Compressor ;

/* Variables and functions */
 int /*<<< orphan*/  AttrOffsetGetAttrNumber (int) ; 
 int /*<<< orphan*/  segment_meta_min_max_builder_update_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  segment_meta_min_max_builder_update_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
row_compressor_append_row(RowCompressor *row_compressor, TupleTableSlot *row)
{
	int col;
	for (col = 0; col < row_compressor->n_input_columns; col++)
	{
		Compressor *compressor = row_compressor->per_column[col].compressor;
		bool is_null;
		Datum val;

		/* if there is no compressor, this must be a segmenter, so just skip */
		if (compressor == NULL)
			continue;

		// TODO since we call getallatts at the beginning, slot_getattr is useless
		//     overhead here, and we should just access the array directly
		val = slot_getattr(row, AttrOffsetGetAttrNumber(col), &is_null);
		if (is_null)
		{
			compressor->append_null(compressor);
			if (row_compressor->per_column[col].min_max_metadata_builder != NULL)
				segment_meta_min_max_builder_update_null(
					row_compressor->per_column[col].min_max_metadata_builder);
		}
		else
		{
			compressor->append_val(compressor, val);
			if (row_compressor->per_column[col].min_max_metadata_builder != NULL)
				segment_meta_min_max_builder_update_val(row_compressor->per_column[col]
															.min_max_metadata_builder,
														val);
		}
	}

	row_compressor->rows_compressed_into_current_value += 1;
}