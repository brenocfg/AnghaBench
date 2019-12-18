#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64 ;
typedef  scalar_t__ uint32 ;
struct TYPE_10__ {int has_nulls; int /*<<< orphan*/  delta_deltas; void* last_delta; void* last_value; int /*<<< orphan*/  compression_algorithm; int /*<<< orphan*/  vl_len_; } ;
struct TYPE_9__ {scalar_t__ num_elements; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_1__ Simple8bRleSerialized ;
typedef  TYPE_2__ DeltaDeltaCompressed ;

/* Variables and functions */
 int /*<<< orphan*/  AllocSizeIsValid (scalar_t__) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  COMPRESSION_ALGORITHM_DELTADELTA ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MaxAllocSize ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 char* bytes_serialize_simple8b_and_advance (char*,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 char* palloc (scalar_t__) ; 
 scalar_t__ simple8brle_serialized_slot_size (TYPE_1__*) ; 
 scalar_t__ simple8brle_serialized_total_size (TYPE_1__*) ; 

__attribute__((used)) static DeltaDeltaCompressed *
delta_delta_from_parts(uint64 last_value, uint64 last_delta, Simple8bRleSerialized *deltas,
					   Simple8bRleSerialized *nulls)
{
	uint32 nulls_size = 0;
	Size compressed_size;
	char *compressed_data;
	DeltaDeltaCompressed *compressed;
	if (nulls != NULL)
		nulls_size = simple8brle_serialized_total_size(nulls);
	compressed_size =
		sizeof(DeltaDeltaCompressed) + simple8brle_serialized_slot_size(deltas) + nulls_size;

	if (!AllocSizeIsValid(compressed_size))
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("compressed size exceeds the maximum allowed (%d)", (int) MaxAllocSize)));

	compressed_data = palloc(compressed_size);
	compressed = (DeltaDeltaCompressed *) compressed_data;
	SET_VARSIZE(&compressed->vl_len_, compressed_size);

	compressed->compression_algorithm = COMPRESSION_ALGORITHM_DELTADELTA;
	compressed->last_value = last_value;
	compressed->last_delta = last_delta;
	compressed->has_nulls = nulls_size != 0 ? 1 : 0;

	compressed_data = (char *) &compressed->delta_deltas;
	compressed_data =
		bytes_serialize_simple8b_and_advance(compressed_data,
											 simple8brle_serialized_total_size(deltas),
											 deltas);
	if (compressed->has_nulls)
	{
		Assert(nulls->num_elements > deltas->num_elements);
		bytes_serialize_simple8b_and_advance(compressed_data, nulls_size, nulls);
	}

	return compressed;
}