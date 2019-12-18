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
struct TYPE_6__ {int /*<<< orphan*/ * nulls; TYPE_1__ const* header; int /*<<< orphan*/  xors; void* num_bits_used_per_xor; int /*<<< orphan*/  leading_zeros; void* tag1s; void* tag0s; } ;
struct TYPE_5__ {scalar_t__ compression_algorithm; int has_nulls; int /*<<< orphan*/  bits_used_in_last_xor_bucket; int /*<<< orphan*/  num_xor_buckets; int /*<<< orphan*/  bits_used_in_last_leading_zeros_bucket; int /*<<< orphan*/  num_leading_zeroes_buckets; } ;
typedef  TYPE_1__ GorillaCompressed ;
typedef  TYPE_2__ CompressedGorillaData ;

/* Variables and functions */
 scalar_t__ COMPRESSION_ALGORITHM_GORILLA ; 
 int /*<<< orphan*/  ERROR ; 
 char* bytes_attach_bit_array_and_advance (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* bytes_deserialize_simple8b_and_advance (char const**) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
compressed_gorilla_data_init_from_pointer(CompressedGorillaData *expanded,
										  const GorillaCompressed *compressed)
{
	bool has_nulls;
	const char *data = (char *) compressed;

	expanded->header = compressed;
	if (expanded->header->compression_algorithm != COMPRESSION_ALGORITHM_GORILLA)
		elog(ERROR, "unknown compression algorithm");

	has_nulls = expanded->header->has_nulls == 1;
	data += sizeof(GorillaCompressed);

	expanded->tag0s = bytes_deserialize_simple8b_and_advance(&data);
	expanded->tag1s = bytes_deserialize_simple8b_and_advance(&data);

	data = bytes_attach_bit_array_and_advance(&expanded->leading_zeros,
											  data,
											  expanded->header->num_leading_zeroes_buckets,
											  expanded->header
												  ->bits_used_in_last_leading_zeros_bucket);

	expanded->num_bits_used_per_xor = bytes_deserialize_simple8b_and_advance(&data);

	data = bytes_attach_bit_array_and_advance(&expanded->xors,
											  data,
											  expanded->header->num_xor_buckets,
											  expanded->header->bits_used_in_last_xor_bucket);

	if (has_nulls)
		expanded->nulls = bytes_deserialize_simple8b_and_advance(&data);
	else
		expanded->nulls = NULL;
}