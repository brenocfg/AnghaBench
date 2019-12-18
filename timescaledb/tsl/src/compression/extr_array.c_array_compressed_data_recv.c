#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_7__ {scalar_t__ val; int /*<<< orphan*/  is_done; } ;
struct TYPE_6__ {scalar_t__ num_elements; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ Simple8bRleDecompressionIterator ;
typedef  TYPE_2__ Simple8bRleDecompressResult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  DatumDeserializer ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayCompressorSerializationInfo ;
typedef  int /*<<< orphan*/  ArrayCompressor ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BINARY_ENCODING ; 
 int /*<<< orphan*/  TEXT_ENCODING ; 
 int /*<<< orphan*/ * array_compressor_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_compressor_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_compressor_append_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * array_compressor_get_serialization_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binary_string_to_datum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_datum_deserializer (int /*<<< orphan*/ ) ; 
 scalar_t__ pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 scalar_t__ pq_getmsgint32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple8brle_decompression_iterator_init_forward (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ simple8brle_decompression_iterator_try_next_forward (TYPE_1__*) ; 
 int /*<<< orphan*/  simple8brle_serialized_recv (int /*<<< orphan*/ ) ; 

ArrayCompressorSerializationInfo *
array_compressed_data_recv(StringInfo buffer, Oid element_type)
{
	ArrayCompressor *compressor = array_compressor_alloc(element_type);
	Simple8bRleDecompressionIterator nulls;
	uint8 has_nulls;
	DatumDeserializer *deser = create_datum_deserializer(element_type);
	bool use_binary_recv;
	uint32 num_elements;
	uint32 i;

	has_nulls = pq_getmsgbyte(buffer) != 0;
	if (has_nulls)
		simple8brle_decompression_iterator_init_forward(&nulls,
														simple8brle_serialized_recv(buffer));

	use_binary_recv = pq_getmsgbyte(buffer) != 0;

	/* This is actually the number of not-null elements */
	num_elements = pq_getmsgint32(buffer);

	/* if there are nulls, use that count instead */
	if (has_nulls)
		num_elements = nulls.num_elements;

	for (i = 0; i < num_elements; i++)
	{
		Datum val;
		if (has_nulls)
		{
			Simple8bRleDecompressResult null =
				simple8brle_decompression_iterator_try_next_forward(&nulls);
			Assert(!null.is_done);
			if (null.val)
			{
				array_compressor_append_null(compressor);
				continue;
			}
		}

		val = binary_string_to_datum(deser,
									 use_binary_recv ? BINARY_ENCODING : TEXT_ENCODING,
									 buffer);

		array_compressor_append(compressor, val);
	}

	return array_compressor_get_serialization_info(compressor);
}