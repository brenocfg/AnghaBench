#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_16__ {int attno; int /*<<< orphan*/  type; int /*<<< orphan*/  typid; } ;
struct TYPE_15__ {int num_columns; int /*<<< orphan*/  hypertable_compression_info; TYPE_6__* columns; int /*<<< orphan*/  varattno_map; } ;
struct TYPE_14__ {scalar_t__ segmentby_column_index; } ;
struct TYPE_13__ {int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; } ;
struct TYPE_12__ {TYPE_1__* ss_ScanTupleSlot; } ;
struct TYPE_11__ {int /*<<< orphan*/  tts_tupleDescriptor; } ;
typedef  TYPE_2__ ScanState ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  TYPE_4__ FormData_hypertable_compression ;
typedef  TYPE_5__ DecompressChunkState ;
typedef  TYPE_6__ DecompressChunkColumnState ;

/* Variables and functions */
 int /*<<< orphan*/  AttrNumberGetAttrOffset (int) ; 
 int /*<<< orphan*/  COMPRESSED_COLUMN ; 
 int /*<<< orphan*/  COUNT_COLUMN ; 
#define  DECOMPRESS_CHUNK_COUNT_ID 129 
#define  DECOMPRESS_CHUNK_SEQUENCE_NUM_ID 128 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEGMENTBY_COLUMN ; 
 int /*<<< orphan*/  SEQUENCE_NUM_COLUMN ; 
 TYPE_3__* TupleDescAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__* get_column_compressioninfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lfirst_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ *) ; 
 TYPE_6__* palloc0 (int) ; 

__attribute__((used)) static void
initialize_column_state(DecompressChunkState *state)
{
	ScanState *ss = (ScanState *) state;
	TupleDesc desc = ss->ss_ScanTupleSlot->tts_tupleDescriptor;
	ListCell *lc;
	int i;

	state->num_columns = list_length(state->varattno_map);

	state->columns = palloc0(state->num_columns * sizeof(DecompressChunkColumnState));

	for (i = 0, lc = list_head(state->varattno_map); i < state->num_columns; lc = lnext(lc), i++)
	{
		DecompressChunkColumnState *column = &state->columns[i];
		column->attno = lfirst_int(lc);

		if (column->attno > 0)
		{
			/* normal column that is also present in uncompressed chunk */
			Form_pg_attribute attribute =
				TupleDescAttr(desc, AttrNumberGetAttrOffset(lfirst_int(lc)));
			FormData_hypertable_compression *ht_info =
				get_column_compressioninfo(state->hypertable_compression_info,
										   NameStr(attribute->attname));

			column->typid = attribute->atttypid;

			if (ht_info->segmentby_column_index > 0)
				column->type = SEGMENTBY_COLUMN;
			else
				column->type = COMPRESSED_COLUMN;
		}
		else
		{
			/* metadata columns */
			switch (column->attno)
			{
				case DECOMPRESS_CHUNK_COUNT_ID:
					column->type = COUNT_COLUMN;
					break;
				case DECOMPRESS_CHUNK_SEQUENCE_NUM_ID:
					column->type = SEQUENCE_NUM_COLUMN;
					break;
				default:
					elog(ERROR, "Invalid column attno \"%d\"", column->attno);
					break;
			}
		}
	}
}