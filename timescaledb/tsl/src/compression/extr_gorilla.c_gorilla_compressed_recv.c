#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* nulls; void* xors; void* num_bits_used_per_xor; void* leading_zeros; void* tag1s; void* tag0s; TYPE_2__* header; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int has_nulls; int /*<<< orphan*/  last_value; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__ GorillaCompressed ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ CompressedGorillaData ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_RETURN_POINTER (int /*<<< orphan*/ ) ; 
 void* bit_array_recv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compressed_gorilla_data_serialize (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_getmsgint64 (int /*<<< orphan*/ ) ; 
 void* simple8brle_serialized_recv (int /*<<< orphan*/ ) ; 

Datum
gorilla_compressed_recv(StringInfo buf)
{
	GorillaCompressed header = { { 0 } };
	CompressedGorillaData data = {
		.header = &header,
	};

	header.has_nulls = pq_getmsgbyte(buf);
	if (header.has_nulls != 0 && header.has_nulls != 1)
		elog(ERROR, "invalid recv in gorilla: bad bool");

	header.last_value = pq_getmsgint64(buf);
	data.tag0s = simple8brle_serialized_recv(buf);
	data.tag1s = simple8brle_serialized_recv(buf);
	data.leading_zeros = bit_array_recv(buf);
	data.num_bits_used_per_xor = simple8brle_serialized_recv(buf);
	data.xors = bit_array_recv(buf);

	if (header.has_nulls)
		data.nulls = simple8brle_serialized_recv(buf);

	PG_RETURN_POINTER(compressed_gorilla_data_serialize(&data));
}