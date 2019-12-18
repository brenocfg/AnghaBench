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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_5__ {int /*<<< orphan*/ * segment_info; int /*<<< orphan*/ * compressor; } ;
struct TYPE_4__ {int n_input_columns; TYPE_2__* per_column; } ;
typedef  TYPE_1__ RowCompressor ;
typedef  TYPE_2__ PerColumn ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AttrOffsetGetAttrNumber (int) ; 
 int /*<<< orphan*/  CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  segment_info_datum_is_in_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool
row_compressor_new_row_is_in_new_group(RowCompressor *row_compressor, TupleTableSlot *row)
{
	int col;
	for (col = 0; col < row_compressor->n_input_columns; col++)
	{
		PerColumn *column = &row_compressor->per_column[col];
		Datum datum = CharGetDatum(0);
		bool is_null;

		if (column->segment_info == NULL)
			continue;

		Assert(column->compressor == NULL);

		datum = slot_getattr(row, AttrOffsetGetAttrNumber(col), &is_null);

		if (!segment_info_datum_is_in_group(column->segment_info, datum, is_null))
			return true;
	}

	return false;
}