#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8 ;
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Simple8bRleSerialized ;
typedef  int /*<<< orphan*/  DeltaDeltaCompressed ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_RETURN_POINTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * delta_delta_from_parts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_getmsgint64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * simple8brle_serialized_recv (int /*<<< orphan*/ ) ; 

Datum
deltadelta_compressed_recv(StringInfo buffer)
{
	uint8 has_nulls;
	uint64 last_value;
	uint64 last_delta;
	Simple8bRleSerialized *delta_deltas;
	Simple8bRleSerialized *nulls = NULL;
	DeltaDeltaCompressed *compressed;

	has_nulls = pq_getmsgbyte(buffer);
	if (has_nulls != 0 && has_nulls != 1)
		elog(ERROR, "invalid recv in deltadelta: bad bool");

	last_value = pq_getmsgint64(buffer);
	last_delta = pq_getmsgint64(buffer);
	delta_deltas = simple8brle_serialized_recv(buffer);
	if (has_nulls)
		nulls = simple8brle_serialized_recv(buffer);

	compressed = delta_delta_from_parts(last_value, last_delta, delta_deltas, nulls);

	PG_RETURN_POINTER(compressed);
}