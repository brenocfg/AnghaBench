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
struct TYPE_5__ {scalar_t__ compression_algorithm; } ;
struct TYPE_4__ {int /*<<< orphan*/  delta_deltas; scalar_t__ has_nulls; int /*<<< orphan*/  last_delta; int /*<<< orphan*/  last_value; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Simple8bRleSerialized ;
typedef  TYPE_1__ DeltaDeltaCompressed ;
typedef  TYPE_2__ CompressedDataHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COMPRESSION_ALGORITHM_DELTADELTA ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pq_sendint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple8brle_serialized_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int simple8brle_serialized_total_size (int /*<<< orphan*/ *) ; 

void
deltadelta_compressed_send(CompressedDataHeader *header, StringInfo buffer)
{
	const DeltaDeltaCompressed *data = (DeltaDeltaCompressed *) header;
	Assert(header->compression_algorithm == COMPRESSION_ALGORITHM_DELTADELTA);
	pq_sendbyte(buffer, data->has_nulls);
	pq_sendint64(buffer, data->last_value);
	pq_sendint64(buffer, data->last_delta);
	simple8brle_serialized_send(buffer, &data->delta_deltas);
	if (data->has_nulls)
	{
		Simple8bRleSerialized *nulls =
			(Simple8bRleSerialized *) (((char *) &data->delta_deltas) +
									   simple8brle_serialized_total_size(&data->delta_deltas));
		simple8brle_serialized_send(buffer, nulls);
	}
}