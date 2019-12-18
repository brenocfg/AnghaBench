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
struct TYPE_8__ {scalar_t__ compression_algorithm; } ;
struct TYPE_7__ {int /*<<< orphan*/  nulls; TYPE_1__* header; int /*<<< orphan*/  xors; int /*<<< orphan*/  num_bits_used_per_xor; int /*<<< orphan*/  leading_zeros; int /*<<< orphan*/  tag1s; int /*<<< orphan*/  tag0s; } ;
struct TYPE_6__ {scalar_t__ has_nulls; int /*<<< orphan*/  last_value; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  GorillaCompressed ;
typedef  TYPE_2__ CompressedGorillaData ;
typedef  TYPE_3__ CompressedDataHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COMPRESSION_ALGORITHM_GORILLA ; 
 int /*<<< orphan*/  bit_array_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compressed_gorilla_data_init_from_pointer (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pq_sendint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple8brle_serialized_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gorilla_compressed_send(CompressedDataHeader *header, StringInfo buf)
{
	CompressedGorillaData data;
	const GorillaCompressed *compressed = (GorillaCompressed *) header;
	Assert(header->compression_algorithm == COMPRESSION_ALGORITHM_GORILLA);

	compressed_gorilla_data_init_from_pointer(&data, compressed);
	pq_sendbyte(buf, data.header->has_nulls);
	pq_sendint64(buf, data.header->last_value);
	simple8brle_serialized_send(buf, data.tag0s);
	simple8brle_serialized_send(buf, data.tag1s);
	bit_array_send(buf, &data.leading_zeros);
	simple8brle_serialized_send(buf, data.num_bits_used_per_xor);
	bit_array_send(buf, &data.xors);
	if (data.header->has_nulls)
		simple8brle_serialized_send(buf, data.nulls);
}