#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * nulls; int /*<<< orphan*/  xors; int /*<<< orphan*/ * num_bits_used_per_xor; int /*<<< orphan*/  leading_zeros; int /*<<< orphan*/ * tag1s; int /*<<< orphan*/ * tag0s; } ;
struct TYPE_7__ {int forward; int /*<<< orphan*/  try_next; int /*<<< orphan*/  element_type; int /*<<< orphan*/  compression_algorithm; } ;
struct TYPE_6__ {int has_nulls; TYPE_2__ base; TYPE_5__ gorilla_data; int /*<<< orphan*/  nulls; int /*<<< orphan*/  xors; int /*<<< orphan*/  num_bits_used; int /*<<< orphan*/  leading_zeros; int /*<<< orphan*/  tag1s; int /*<<< orphan*/  tag0s; scalar_t__ prev_xor_bits_used; scalar_t__ prev_leading_zeroes; scalar_t__ prev_val; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ GorillaDecompressionIterator ;
typedef  TYPE_2__ DecompressionIterator ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  COMPRESSION_ALGORITHM_GORILLA ; 
 int /*<<< orphan*/  bit_array_iterator_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compressed_gorilla_data_init_from_datum (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gorilla_decompression_iterator_try_next_forward ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  simple8brle_decompression_iterator_init_forward (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DecompressionIterator *
gorilla_decompression_iterator_from_datum_forward(Datum gorilla_compressed, Oid element_type)
{
	GorillaDecompressionIterator *iterator = palloc(sizeof(*iterator));
	iterator->base.compression_algorithm = COMPRESSION_ALGORITHM_GORILLA;
	iterator->base.forward = true;
	iterator->base.element_type = element_type;
	iterator->base.try_next = gorilla_decompression_iterator_try_next_forward;
	iterator->prev_val = 0;
	iterator->prev_leading_zeroes = 0;
	iterator->prev_xor_bits_used = 0;
	compressed_gorilla_data_init_from_datum(&iterator->gorilla_data, gorilla_compressed);

	simple8brle_decompression_iterator_init_forward(&iterator->tag0s, iterator->gorilla_data.tag0s);
	simple8brle_decompression_iterator_init_forward(&iterator->tag1s, iterator->gorilla_data.tag1s);
	bit_array_iterator_init(&iterator->leading_zeros, &iterator->gorilla_data.leading_zeros);
	simple8brle_decompression_iterator_init_forward(&iterator->num_bits_used,
													iterator->gorilla_data.num_bits_used_per_xor);
	bit_array_iterator_init(&iterator->xors, &iterator->gorilla_data.xors);

	iterator->has_nulls = iterator->gorilla_data.nulls != NULL;
	if (iterator->has_nulls)
		simple8brle_decompression_iterator_init_forward(&iterator->nulls,
														iterator->gorilla_data.nulls);

	return &iterator->base;
}