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
struct TYPE_5__ {scalar_t__ num_elements; char* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  serializer; TYPE_2__ data; int /*<<< orphan*/  sizes; int /*<<< orphan*/  nulls; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ ArrayCompressor ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PG_DETOAST_DATUM_PACKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  char_vec_reserve (TYPE_2__*,scalar_t__) ; 
 scalar_t__ datum_get_bytes_size (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ datum_serializer_value_may_be_toasted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datum_to_bytes_and_advance (int /*<<< orphan*/ ,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple8brle_compressor_append (int /*<<< orphan*/ *,scalar_t__) ; 

void
array_compressor_append(ArrayCompressor *compressor, Datum val)
{
	Size datum_size_and_align;
	char *start_ptr;
	simple8brle_compressor_append(&compressor->nulls, 0);
	if (datum_serializer_value_may_be_toasted(compressor->serializer))
		val = PointerGetDatum(PG_DETOAST_DATUM_PACKED(val));

	datum_size_and_align =
		datum_get_bytes_size(compressor->serializer, compressor->data.num_elements, val) -
		compressor->data.num_elements;

	simple8brle_compressor_append(&compressor->sizes, datum_size_and_align);

	/* datum_to_bytes_and_advance will zero any padding bytes, so we need not do so here */
	char_vec_reserve(&compressor->data, datum_size_and_align);
	start_ptr = compressor->data.data + compressor->data.num_elements;
	compressor->data.num_elements += datum_size_and_align;

	datum_to_bytes_and_advance(compressor->serializer, start_ptr, &datum_size_and_align, val);
	Assert(datum_size_and_align == 0);
}