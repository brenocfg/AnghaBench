#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* sizes; int /*<<< orphan*/ * nulls; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; scalar_t__ is_null; int /*<<< orphan*/  is_done; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_elements; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  DecompressionIterator ;
typedef  TYPE_2__ DecompressResult ;
typedef  int /*<<< orphan*/  DatumSerializer ;
typedef  scalar_t__ BinaryStringEncoding ;
typedef  TYPE_3__ ArrayCompressedData ;

/* Variables and functions */
 scalar_t__ BINARY_ENCODING ; 
 TYPE_3__ array_compressed_data_from_bytes (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * array_decompression_iterator_alloc_forward (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ array_decompression_iterator_try_next_forward (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_datum_serializer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datum_append_to_binary_string (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ datum_serializer_binary_string_encoding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple8brle_serialized_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
array_compressed_data_send(StringInfo buffer, const char *serialized_data, Size data_size,
						   Oid element_type, bool has_nulls)
{
	ArrayCompressedData data;
	DecompressionIterator *data_iter;
	DecompressResult datum;
	DatumSerializer *serializer = create_datum_serializer(element_type);
	BinaryStringEncoding encoding = datum_serializer_binary_string_encoding(serializer);

	data = array_compressed_data_from_bytes(serialized_data, data_size, element_type, has_nulls);

	pq_sendbyte(buffer, data.nulls != NULL);
	if (data.nulls != NULL)
		simple8brle_serialized_send(buffer, data.nulls);

	pq_sendbyte(buffer, encoding == BINARY_ENCODING);

	/*
	 * we do not send data.sizes because the sizes need not be the same once
	 * deserialized, and we will need to recalculate them on recv. We do need
	 * to send the number of elements, which is always the same as the number
	 * of sizes.
	 */
	pq_sendint32(buffer, data.sizes->num_elements);
	data_iter = array_decompression_iterator_alloc_forward(serialized_data,
														   data_size,
														   element_type,
														   has_nulls);
	for (datum = array_decompression_iterator_try_next_forward(data_iter); !datum.is_done;
		 datum = array_decompression_iterator_try_next_forward(data_iter))
	{
		if (datum.is_null)
			continue;

		datum_append_to_binary_string(serializer, encoding, buffer, datum.val);
	}
}