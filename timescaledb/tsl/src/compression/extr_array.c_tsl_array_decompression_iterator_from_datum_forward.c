#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_3__ {scalar_t__ compression_algorithm; scalar_t__ element_type; int has_nulls; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  DecompressionIterator ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ ArrayCompressed ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COMPRESSION_ALGORITHM_ARRAY ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PG_DETOAST_DATUM (int /*<<< orphan*/ ) ; 
 int VARSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/ * array_decompression_iterator_alloc_forward (char const*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

DecompressionIterator *
tsl_array_decompression_iterator_from_datum_forward(Datum compressed_array, Oid element_type)
{
	ArrayCompressed *compressed_array_header;
	uint32 data_size;
	const char *compressed_data = (void *) PG_DETOAST_DATUM(compressed_array);

	compressed_array_header = (ArrayCompressed *) compressed_data;
	compressed_data += sizeof(*compressed_array_header);

	Assert(compressed_array_header->compression_algorithm == COMPRESSION_ALGORITHM_ARRAY);

	data_size = VARSIZE(compressed_array_header);
	data_size -= sizeof(*compressed_array_header);

	if (element_type != compressed_array_header->element_type)
		elog(ERROR, "trying to decompress the wrong type");

	return array_decompression_iterator_alloc_forward(compressed_data,
													  data_size,
													  compressed_array_header->element_type,
													  compressed_array_header->has_nulls == 1);
}