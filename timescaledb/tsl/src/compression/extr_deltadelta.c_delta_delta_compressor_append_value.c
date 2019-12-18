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
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ int64 ;
struct TYPE_3__ {int /*<<< orphan*/  nulls; int /*<<< orphan*/  delta_delta; scalar_t__ prev_delta; scalar_t__ prev_val; } ;
typedef  TYPE_1__ DeltaDeltaCompressor ;

/* Variables and functions */
 int /*<<< orphan*/  simple8brle_compressor_append (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zig_zag_encode (scalar_t__) ; 

void
delta_delta_compressor_append_value(DeltaDeltaCompressor *compressor, int64 next_val)
{
	uint64 delta;
	uint64 delta_delta;
	uint64 encoded;

	/*
	 * We perform all arithmetic using unsigned values due to C's overflow rules:
	 * signed integer overflow is undefined behavior, so if we have a very large delta,
	 * this code is without meaning, while unsigned overflow is 2's complement, so even
	 * very large delta work the same as any other
	 */

	/* step 1: delta of deltas */
	delta = ((uint64) next_val) - compressor->prev_val;
	delta_delta = delta - compressor->prev_delta;

	compressor->prev_val = next_val;
	compressor->prev_delta = delta;

	/* step 2: ZigZag encode */
	encoded = zig_zag_encode(delta_delta);

	/* step 3: simple8b/RTE */
	simple8brle_compressor_append(&compressor->delta_delta, encoded);
	simple8brle_compressor_append(&compressor->nulls, 0);
}