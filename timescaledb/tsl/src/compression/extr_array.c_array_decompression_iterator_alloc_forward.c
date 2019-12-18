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
struct TYPE_9__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; int /*<<< orphan*/ * sizes; int /*<<< orphan*/ * nulls; } ;
struct TYPE_7__ {int forward; int /*<<< orphan*/  element_type; int /*<<< orphan*/  try_next; int /*<<< orphan*/  compression_algorithm; } ;
struct TYPE_8__ {int has_nulls; TYPE_1__ base; int /*<<< orphan*/  deserializer; scalar_t__ data_offset; int /*<<< orphan*/  num_data_bytes; int /*<<< orphan*/  data; int /*<<< orphan*/  sizes; int /*<<< orphan*/  nulls; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DecompressionIterator ;
typedef  TYPE_2__ ArrayDecompressionIterator ;
typedef  TYPE_3__ ArrayCompressedData ;

/* Variables and functions */
 int /*<<< orphan*/  COMPRESSION_ALGORITHM_ARRAY ; 
 TYPE_3__ array_compressed_data_from_bytes (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  array_decompression_iterator_try_next_forward ; 
 int /*<<< orphan*/  create_datum_deserializer (int /*<<< orphan*/ ) ; 
 TYPE_2__* palloc (int) ; 
 int /*<<< orphan*/  simple8brle_decompression_iterator_init_forward (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DecompressionIterator *
array_decompression_iterator_alloc_forward(const char *serialized_data, Size data_size,
										   Oid element_type, bool has_nulls)
{
	ArrayCompressedData data =
		array_compressed_data_from_bytes(serialized_data, data_size, element_type, has_nulls);

	ArrayDecompressionIterator *iterator = palloc(sizeof(*iterator));
	iterator->base.compression_algorithm = COMPRESSION_ALGORITHM_ARRAY;
	iterator->base.forward = true;
	iterator->base.element_type = element_type;
	iterator->base.try_next = array_decompression_iterator_try_next_forward;

	iterator->has_nulls = data.nulls != NULL;
	if (iterator->has_nulls)
		simple8brle_decompression_iterator_init_forward(&iterator->nulls, data.nulls);

	simple8brle_decompression_iterator_init_forward(&iterator->sizes, data.sizes);

	iterator->data = data.data;
	iterator->num_data_bytes = data.data_len;
	iterator->data_offset = 0;
	iterator->deserializer = create_datum_deserializer(iterator->base.element_type);

	return &iterator->base;
}