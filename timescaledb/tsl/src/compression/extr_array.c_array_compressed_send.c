#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_6__ {int has_nulls; int /*<<< orphan*/  element_type; } ;
struct TYPE_5__ {scalar_t__ compression_algorithm; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ CompressedDataHeader ;
typedef  TYPE_2__ ArrayCompressed ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COMPRESSION_ALGORITHM_ARRAY ; 
 int VARSIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  array_compressed_data_send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  type_append_to_binary_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
array_compressed_send(CompressedDataHeader *header, StringInfo buffer)
{
	const char *compressed_data = (char *) header;
	uint32 data_size;
	ArrayCompressed *compressed_array_header;

	Assert(header->compression_algorithm == COMPRESSION_ALGORITHM_ARRAY);
	compressed_array_header = (ArrayCompressed *) header;

	compressed_data += sizeof(*compressed_array_header);

	data_size = VARSIZE(compressed_array_header);
	data_size -= sizeof(*compressed_array_header);

	pq_sendbyte(buffer, compressed_array_header->has_nulls == true);

	type_append_to_binary_string(compressed_array_header->element_type, buffer);

	array_compressed_data_send(buffer,
							   compressed_data,
							   data_size,
							   compressed_array_header->element_type,
							   compressed_array_header->has_nulls);
}