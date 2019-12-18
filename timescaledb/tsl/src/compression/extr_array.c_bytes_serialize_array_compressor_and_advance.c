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
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {scalar_t__ num_elements; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {scalar_t__ total; TYPE_1__ data; int /*<<< orphan*/ * sizes; int /*<<< orphan*/ * nulls; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_2__ ArrayCompressorSerializationInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* bytes_serialize_simple8b_and_advance (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ simple8brle_serialized_total_size (int /*<<< orphan*/ *) ; 

char *
bytes_serialize_array_compressor_and_advance(char *dst, Size dst_size,
											 ArrayCompressorSerializationInfo *info)
{
	uint32 sizes_bytes = simple8brle_serialized_total_size(info->sizes);

	Assert(dst_size == info->total);

	if (info->nulls != NULL)
	{
		uint32 nulls_bytes = simple8brle_serialized_total_size(info->nulls);
		Assert(dst_size >= nulls_bytes);
		dst = bytes_serialize_simple8b_and_advance(dst, nulls_bytes, info->nulls);
		dst_size -= nulls_bytes;
	}

	Assert(dst_size >= sizes_bytes);
	dst = bytes_serialize_simple8b_and_advance(dst, sizes_bytes, info->sizes);
	dst_size -= sizes_bytes;

	Assert(dst_size == info->data.num_elements);
	memcpy(dst, info->data.data, info->data.num_elements);
	return dst + info->data.num_elements;
}