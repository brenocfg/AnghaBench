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
struct TYPE_4__ {unsigned char* buffer; int run; int pixel; int lastpixel; int /*<<< orphan*/  chain; scalar_t__ len; } ;
typedef  TYPE_1__ fz_thunder ;
struct TYPE_5__ {unsigned char* rp; unsigned char* wp; int /*<<< orphan*/  pos; TYPE_1__* state; } ;
typedef  TYPE_2__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int EOF ; 
 int fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
next_thunder(fz_context *ctx, fz_stream *stm, size_t max)
{
	fz_thunder *state = stm->state;
	unsigned char *p = state->buffer;
	unsigned char *ep;
	int c, v, i, pixels, index;

	if (max > (size_t)state->len)
		max = (size_t)state->len;

	ep = p + max;

	c = 0;
	while (p < ep && c >= 0)
	{
		pixels = 0;
		v = 0;

		while (pixels < 2)
		{
			if (state->run > 0)
			{
				v <<= 4;
				v |= state->pixel & 0xf;
				state->pixel >>= 4;
				state->run--;
				pixels++;

				if (state->run > 2)
					state->pixel |= ((state->pixel >> 4) & 0xf) << 8;
			}
			else
			{
				c = fz_read_byte(ctx, state->chain);
				if (c < 0)
					break;

				switch ((c >> 6) & 0x3)
				{
				case 0x0: /* run of pixels identical to last pixel */
					state->run = c;
					state->pixel = (state->lastpixel << 8) | (state->lastpixel << 4) | (state->lastpixel << 0);
					break;

				case 0x1: /* three pixels with 2bit deltas to last pixel */
					for (i = 0; i < 3; i++)
					{
						static const int deltas[] = { 0, 1, 0, -1 };
						index = (c >> (4 - i * 2)) & 0x3;
						if (index == 2)
							continue;

						state->lastpixel = (state->lastpixel + deltas[index]) & 0xf;
						state->pixel <<= 4;
						state->pixel |= state->lastpixel;
						state->run++;
					}
					break;

				case 0x2: /* two pixels with 3bit deltas to last pixel */
					for (i = 0; i < 2; i++)
					{
						static const int deltas[] = { 0, 1, 2, 3, 0, -3, -2, -1 };
						index = (c >> (3 - i * 3)) & 0x7;
						if (index == 4)
							continue;

						state->lastpixel = (state->lastpixel + deltas[index]) & 0xf;
						state->pixel <<= 4;
						state->pixel |= state->lastpixel;
						state->run++;
					}
					break;

				case 0x3: /* a single raw 4bit pixel */
					state->run = 1;
					state->pixel = c & 0xf;
					state->lastpixel = state->pixel & 0xf;
					break;
				}
			}
		}

		if (pixels)
			*p++ = v;
	}

	stm->rp = state->buffer;
	stm->wp = p;
	stm->pos += p - state->buffer;

	if (stm->rp != p)
		return *stm->rp++;
	return EOF;
}