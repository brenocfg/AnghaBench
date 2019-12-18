#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int* tts_isnull; int /*<<< orphan*/ * tts_values; } ;
typedef  TYPE_5__ TupleTableSlot ;
struct TYPE_23__ {int isnull; int /*<<< orphan*/  value; } ;
struct TYPE_22__ {TYPE_10__* iterator; } ;
struct TYPE_27__ {int type; TYPE_4__ segmentby; int /*<<< orphan*/  attno; TYPE_3__ compressed; } ;
struct TYPE_20__ {TYPE_5__* ss_ScanTupleSlot; } ;
struct TYPE_21__ {int /*<<< orphan*/  custom_ps; TYPE_1__ ss; } ;
struct TYPE_26__ {int initialized; int num_columns; int /*<<< orphan*/  counter; TYPE_8__* columns; TYPE_2__ csstate; } ;
struct TYPE_25__ {int is_null; int /*<<< orphan*/  val; int /*<<< orphan*/  is_done; } ;
struct TYPE_19__ {TYPE_6__ (* try_next ) (TYPE_10__*) ;} ;
typedef  TYPE_6__ DecompressResult ;
typedef  TYPE_7__ DecompressChunkState ;
typedef  TYPE_8__ DecompressChunkColumnState ;
typedef  size_t AttrNumber ;

/* Variables and functions */
 size_t AttrNumberGetAttrOffset (int /*<<< orphan*/ ) ; 
#define  COMPRESSED_COLUMN 131 
#define  COUNT_COLUMN 130 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecClearTuple (TYPE_5__*) ; 
 TYPE_5__* ExecProcNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_5__*) ; 
#define  SEGMENTBY_COLUMN 129 
#define  SEQUENCE_NUM_COLUMN 128 
 scalar_t__ TupIsNull (TYPE_5__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  initialize_batch (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 TYPE_6__ stub1 (TYPE_10__*) ; 

__attribute__((used)) static TupleTableSlot *
decompress_chunk_create_tuple(DecompressChunkState *state)
{
	TupleTableSlot *slot = state->csstate.ss.ss_ScanTupleSlot;
	bool batch_done = false;
	int i;

	while (true)
	{
		if (!state->initialized)
		{
			TupleTableSlot *subslot = ExecProcNode(linitial(state->csstate.custom_ps));

			if (TupIsNull(subslot))
				return NULL;

			batch_done = false;
			initialize_batch(state, subslot);
		}

		ExecClearTuple(slot);

		for (i = 0; i < state->num_columns; i++)
		{
			DecompressChunkColumnState *column = &state->columns[i];
			switch (column->type)
			{
				case COUNT_COLUMN:
					if (state->counter <= 0)
						/*
						 * we continue checking other columns even if counter
						 * reaches zero to sanity check all columns are in sync
						 * and agree about batch end
						 */
						batch_done = true;
					else
						state->counter--;
					break;
				case COMPRESSED_COLUMN:
				{
					AttrNumber attr = AttrNumberGetAttrOffset(column->attno);

					if (column->compressed.iterator != NULL)
					{
						DecompressResult result;
						result = column->compressed.iterator->try_next(column->compressed.iterator);

						if (result.is_done)
						{
							batch_done = true;
							continue;
						}
						else if (batch_done)
						{
							/*
							 * since the count column is the first column batch_done
							 * might be true if compressed column is out of sync with
							 * the batch counter.
							 */
							elog(ERROR, "compressed column out of sync with batch counter");
						}

						slot->tts_values[attr] = result.val;
						slot->tts_isnull[attr] = result.is_null;
					}
					else
						slot->tts_isnull[attr] = true;

					break;
				}
				case SEGMENTBY_COLUMN:
				{
					AttrNumber attr = AttrNumberGetAttrOffset(column->attno);

					slot->tts_values[attr] = column->segmentby.value;
					slot->tts_isnull[attr] = column->segmentby.isnull;
					break;
				}
				case SEQUENCE_NUM_COLUMN:
					/*
					 * nothing to do here for sequence number
					 * we only needed this for sorting in node below
					 */
					break;
			}
		}

		if (batch_done)
		{
			state->initialized = false;
			continue;
		}

		ExecStoreVirtualTuple(slot);

		return slot;
	}
}