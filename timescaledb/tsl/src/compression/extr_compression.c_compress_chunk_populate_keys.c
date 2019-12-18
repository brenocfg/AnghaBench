#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int16 ;
struct TYPE_6__ {size_t segmentby_column_index; size_t orderby_column_index; int /*<<< orphan*/  attname; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ColumnCompressionInfo ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AttributeNumberIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ COMPRESSIONCOL_IS_ORDER_BY (TYPE_1__ const*) ; 
 scalar_t__ COMPRESSIONCOL_IS_SEGMENT_BY (TYPE_1__ const*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_attnum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* palloc (int) ; 

__attribute__((used)) static int16 *
compress_chunk_populate_keys(Oid in_table, const ColumnCompressionInfo **columns, int n_columns,
							 int *n_keys_out, const ColumnCompressionInfo ***keys_out)
{
	int16 *column_offsets = palloc(sizeof(*column_offsets) * n_columns);

	int i;
	int n_segment_keys = 0;
	*n_keys_out = 0;

	for (i = 0; i < n_columns; i++)
	{
		if (COMPRESSIONCOL_IS_SEGMENT_BY(columns[i]))
			n_segment_keys += 1;

		if (COMPRESSIONCOL_IS_SEGMENT_BY(columns[i]) || COMPRESSIONCOL_IS_ORDER_BY(columns[i]))
			*n_keys_out += 1;
	}

	if (*n_keys_out == 0)
		elog(ERROR, "compression should be configured with an orderby or segment by");

	*keys_out = palloc(sizeof(**keys_out) * *n_keys_out);

	for (i = 0; i < n_columns; i++)
	{
		const ColumnCompressionInfo *column = columns[i];
		/* valid values for segmentby_columnn_index and orderby_column_index
		   are > 0 */
		int16 segment_offset = column->segmentby_column_index - 1;
		int16 orderby_offset = column->orderby_column_index - 1;
		AttrNumber compressed_att;
		if (COMPRESSIONCOL_IS_SEGMENT_BY(column))
			(*keys_out)[segment_offset] = column;
		else if (COMPRESSIONCOL_IS_ORDER_BY(column))
			(*keys_out)[n_segment_keys + orderby_offset] = column;

		compressed_att = get_attnum(in_table, NameStr(column->attname));
		if (!AttributeNumberIsValid(compressed_att))
			elog(ERROR, "could not find compressed column for \"%s\"", NameStr(column->attname));

		column_offsets[i] = AttrNumberGetAttrOffset(compressed_att);
	}

	return column_offsets;
}