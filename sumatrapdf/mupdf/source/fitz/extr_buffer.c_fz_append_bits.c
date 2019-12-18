#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int unused_bits; int len; unsigned int* data; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_ensure_buffer (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

void
fz_append_bits(fz_context *ctx, fz_buffer *buf, int val, int bits)
{
	int shift;

	/* Throughout this code, the invariant is that we need to write the
	 * bottom 'bits' bits of 'val' into the stream. On entry we assume
	 * that val & ((1<<bits)-1) == val, but we do not rely on this after
	 * having written the first partial byte. */

	if (bits == 0)
		return;

	/* buf->len always covers all the bits in the buffer, including
	 * any unused ones in the last byte, which will always be 0.
	 * buf->unused_bits = the number of unused bits in the last byte.
	 */

	/* Find the amount we need to shift val up by so that it will be in
	 * the correct position to be inserted into any existing data byte. */
	shift = (buf->unused_bits - bits);

	/* Extend the buffer as required before we start; that way we never
	 * fail part way during writing. If shift < 0, then we'll need -shift
	 * more bits. */
	if (shift < 0)
	{
		int extra = (7-shift)>>3; /* Round up to bytes */
		fz_ensure_buffer(ctx, buf, buf->len + extra);
	}

	/* Write any bits that will fit into the existing byte */
	if (buf->unused_bits)
	{
		buf->data[buf->len-1] |= (shift >= 0 ? (((unsigned int)val)<<shift) : (((unsigned int)val)>>-shift));
		if (shift >= 0)
		{
			/* If we were shifting up, we're done. */
			buf->unused_bits -= bits;
			return;
		}
		/* The number of bits left to write is the number that didn't
		 * fit in this first byte. */
		bits = -shift;
	}

	/* Write any whole bytes */
	while (bits >= 8)
	{
		bits -= 8;
		buf->data[buf->len++] = val>>bits;
	}

	/* Write trailing bits (with 0's in unused bits) */
	if (bits > 0)
	{
		bits = 8-bits;
		buf->data[buf->len++] = val<<bits;
	}
	buf->unused_bits = bits;
}