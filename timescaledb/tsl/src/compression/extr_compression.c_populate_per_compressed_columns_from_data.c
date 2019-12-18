#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int16 ;
struct TYPE_7__ {int /*<<< orphan*/ * (* iterator_init_forward ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {size_t compression_algorithm; } ;
struct TYPE_5__ {scalar_t__ decompressed_column_offset; int is_null; scalar_t__ val; int /*<<< orphan*/  decompressed_type; int /*<<< orphan*/ * iterator; scalar_t__ is_compressed; } ;
typedef  TYPE_1__ PerCompressedColumn ;
typedef  scalar_t__ Datum ;
typedef  TYPE_2__ CompressedDataHeader ;

/* Variables and functions */
 scalar_t__ PG_DETOAST_DATUM (scalar_t__) ; 
 int /*<<< orphan*/  PointerGetDatum (char*) ; 
 TYPE_4__* definitions ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
populate_per_compressed_columns_from_data(PerCompressedColumn *per_compressed_cols, int16 num_cols,
										  Datum *compressed_datums, bool *compressed_is_nulls)
{
	for (int16 col = 0; col < num_cols; col++)
	{
		PerCompressedColumn *per_col = &per_compressed_cols[col];
		if (per_col->decompressed_column_offset < 0)
			continue;

		per_col->is_null = compressed_is_nulls[col];
		if (per_col->is_null)
		{
			per_col->is_null = true;
			per_col->iterator = NULL;
			per_col->val = 0;
			continue;
		}

		if (per_col->is_compressed)
		{
			char *data = (char *) PG_DETOAST_DATUM(compressed_datums[col]);
			CompressedDataHeader *header = (CompressedDataHeader *) data;

			per_col->iterator =
				definitions[header->compression_algorithm]
					.iterator_init_forward(PointerGetDatum(data), per_col->decompressed_type);
		}
		else
			per_col->val = compressed_datums[col];
	}
}