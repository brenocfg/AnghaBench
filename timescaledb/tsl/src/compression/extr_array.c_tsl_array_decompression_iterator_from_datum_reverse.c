#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_12__ {scalar_t__ compression_algorithm; scalar_t__ element_type; int /*<<< orphan*/  has_nulls; } ;
struct TYPE_11__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; int /*<<< orphan*/ * sizes; int /*<<< orphan*/ * nulls; } ;
struct TYPE_9__ {int forward; scalar_t__ element_type; int /*<<< orphan*/  try_next; scalar_t__ compression_algorithm; } ;
struct TYPE_10__ {int has_nulls; TYPE_1__ base; int /*<<< orphan*/  deserializer; int /*<<< orphan*/  num_data_bytes; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  data; int /*<<< orphan*/  sizes; int /*<<< orphan*/  nulls; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ DecompressionIterator ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ ArrayDecompressionIterator ;
typedef  TYPE_3__ ArrayCompressedData ;
typedef  TYPE_4__ ArrayCompressed ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COMPRESSION_ALGORITHM_ARRAY ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PG_DETOAST_DATUM (int /*<<< orphan*/ ) ; 
 int VARSIZE (TYPE_4__*) ; 
 TYPE_3__ array_compressed_data_from_bytes (char const*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_decompression_iterator_try_next_reverse ; 
 int /*<<< orphan*/  create_datum_deserializer (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* palloc (int) ; 
 int /*<<< orphan*/  simple8brle_decompression_iterator_init_reverse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DecompressionIterator *
tsl_array_decompression_iterator_from_datum_reverse(Datum compressed_array, Oid element_type)
{
	ArrayCompressed *compressed_array_header;
	uint32 data_size;
	ArrayCompressedData array_compressed_data;
	ArrayDecompressionIterator *iterator = palloc(sizeof(*iterator));
	const char *compressed_data = (void *) PG_DETOAST_DATUM(compressed_array);
	iterator->base.compression_algorithm = COMPRESSION_ALGORITHM_ARRAY;
	iterator->base.forward = false;
	iterator->base.element_type = element_type;
	iterator->base.try_next = array_decompression_iterator_try_next_reverse;

	compressed_array_header = (ArrayCompressed *) compressed_data;
	compressed_data += sizeof(*compressed_array_header);

	Assert(compressed_array_header->compression_algorithm == COMPRESSION_ALGORITHM_ARRAY);
	if (element_type != compressed_array_header->element_type)
		elog(ERROR, "trying to decompress the wrong type");

	data_size = VARSIZE(compressed_array_header);
	data_size -= sizeof(*compressed_array_header);

	array_compressed_data = array_compressed_data_from_bytes(compressed_data,
															 data_size,
															 compressed_array_header->element_type,
															 compressed_array_header->has_nulls);

	iterator->has_nulls = array_compressed_data.nulls != NULL;
	if (iterator->has_nulls)
		simple8brle_decompression_iterator_init_reverse(&iterator->nulls,
														array_compressed_data.nulls);

	simple8brle_decompression_iterator_init_reverse(&iterator->sizes, array_compressed_data.sizes);

	iterator->data = array_compressed_data.data;
	iterator->num_data_bytes = array_compressed_data.data_len;
	iterator->data_offset = iterator->num_data_bytes;
	iterator->deserializer = create_datum_deserializer(iterator->base.element_type);

	return &iterator->base;
}