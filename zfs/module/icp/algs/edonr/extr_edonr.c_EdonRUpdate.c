#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  const uint64_t ;
typedef  int /*<<< orphan*/  const uint32_t ;
struct TYPE_9__ {scalar_t__ LastPart; int /*<<< orphan*/  DoublePipe; } ;
struct TYPE_8__ {scalar_t__ LastPart; int /*<<< orphan*/  DoublePipe; } ;
struct TYPE_7__ {int hashbitlen; int unprocessed_bits; size_t bits_processed; } ;
typedef  TYPE_1__ EdonRState ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EDONR_VALID_HASHBITLEN (int) ; 
 int EdonR256_BLOCK_SIZE ; 
 int EdonR512_BLOCK_SIZE ; 
 size_t Q256 (size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 size_t Q512 (size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,scalar_t__,int) ; 
 TYPE_4__* hashState256 (TYPE_1__*) ; 
 TYPE_2__* hashState512 (TYPE_1__*) ; 

void
EdonRUpdate(EdonRState *state, const uint8_t *data, size_t databitlen)
{
	uint32_t *data32;
	uint64_t *data64;

	size_t bits_processed;

	ASSERT(EDONR_VALID_HASHBITLEN(state->hashbitlen));
	switch (state->hashbitlen) {
	case 224:
	case 256:
		if (state->unprocessed_bits > 0) {
			/* LastBytes = databitlen / 8 */
			int LastBytes = (int)databitlen >> 3;

			ASSERT(state->unprocessed_bits + databitlen <=
			    EdonR256_BLOCK_SIZE * 8);

			bcopy(data, hashState256(state)->LastPart
			    + (state->unprocessed_bits >> 3), LastBytes);
			state->unprocessed_bits += (int)databitlen;
			databitlen = state->unprocessed_bits;
			/* LINTED E_BAD_PTR_CAST_ALIGN */
			data32 = (uint32_t *)hashState256(state)->LastPart;
		} else
			/* LINTED E_BAD_PTR_CAST_ALIGN */
			data32 = (uint32_t *)data;

		bits_processed = Q256(databitlen, data32,
		    hashState256(state)->DoublePipe);
		state->bits_processed += bits_processed;
		databitlen -= bits_processed;
		state->unprocessed_bits = (int)databitlen;
		if (databitlen > 0) {
			/* LastBytes = Ceil(databitlen / 8) */
			int LastBytes =
			    ((~(((-(int)databitlen) >> 3) & 0x01ff)) +
			    1) & 0x01ff;

			data32 += bits_processed >> 5;	/* byte size update */
			bcopy(data32, hashState256(state)->LastPart, LastBytes);
		}
		break;

	case 384:
	case 512:
		if (state->unprocessed_bits > 0) {
			/* LastBytes = databitlen / 8 */
			int LastBytes = (int)databitlen >> 3;

			ASSERT(state->unprocessed_bits + databitlen <=
			    EdonR512_BLOCK_SIZE * 8);

			bcopy(data, hashState512(state)->LastPart
			    + (state->unprocessed_bits >> 3), LastBytes);
			state->unprocessed_bits += (int)databitlen;
			databitlen = state->unprocessed_bits;
			/* LINTED E_BAD_PTR_CAST_ALIGN */
			data64 = (uint64_t *)hashState512(state)->LastPart;
		} else
			/* LINTED E_BAD_PTR_CAST_ALIGN */
			data64 = (uint64_t *)data;

		bits_processed = Q512(databitlen, data64,
		    hashState512(state)->DoublePipe);
		state->bits_processed += bits_processed;
		databitlen -= bits_processed;
		state->unprocessed_bits = (int)databitlen;
		if (databitlen > 0) {
			/* LastBytes = Ceil(databitlen / 8) */
			int LastBytes =
			    ((~(((-(int)databitlen) >> 3) & 0x03ff)) +
			    1) & 0x03ff;

			data64 += bits_processed >> 6;	/* byte size update */
			bcopy(data64, hashState512(state)->LastPart, LastBytes);
		}
		break;
	}
}