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
struct TYPE_3__ {char const* data; int /*<<< orphan*/  data_len; int /*<<< orphan*/ * sizes; int /*<<< orphan*/ * nulls; int /*<<< orphan*/  element_type; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Simple8bRleSerialized ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ArrayCompressedData ;

/* Variables and functions */
 void* bytes_deserialize_simple8b_and_advance (char const**) ; 
 scalar_t__ simple8brle_serialized_total_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ArrayCompressedData
array_compressed_data_from_bytes(const char *serialized_data, Size data_size, Oid element_type,
								 bool has_nulls)
{
	ArrayCompressedData data = { .element_type = element_type };

	if (has_nulls)
	{
		Simple8bRleSerialized *nulls = bytes_deserialize_simple8b_and_advance(&serialized_data);
		data.nulls = nulls;
		data_size -= simple8brle_serialized_total_size(nulls);
	}

	data.sizes = bytes_deserialize_simple8b_and_advance(&serialized_data);
	data_size -= simple8brle_serialized_total_size(data.sizes);

	data.data = serialized_data;
	data.data_len = data_size;

	return data;
}