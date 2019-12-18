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
typedef  int /*<<< orphan*/  word ;
struct TYPE_4__ {unsigned char* rp; unsigned char* wp; int /*<<< orphan*/  pos; TYPE_2__* state; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {unsigned char* buffer; int eod; int /*<<< orphan*/  chain; } ;
typedef  TYPE_2__ fz_a85d ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iswhite (int) ; 

__attribute__((used)) static int
next_a85d(fz_context *ctx, fz_stream *stm, size_t max)
{
	fz_a85d *state = stm->state;
	unsigned char *p = state->buffer;
	unsigned char *ep;
	int count = 0;
	int word = 0;
	int c;

	if (state->eod)
		return EOF;

	if (max > sizeof(state->buffer))
		max = sizeof(state->buffer);

	ep = p + max;
	while (p < ep)
	{
		c = fz_read_byte(ctx, state->chain);
		if (c < 0)
			break;

		if (c >= '!' && c <= 'u')
		{
			if (count == 4)
			{
				word = word * 85 + (c - '!');

				*p++ = (word >> 24) & 0xff;
				*p++ = (word >> 16) & 0xff;
				*p++ = (word >> 8) & 0xff;
				*p++ = (word) & 0xff;

				word = 0;
				count = 0;
			}
			else
			{
				word = word * 85 + (c - '!');
				count ++;
			}
		}

		else if (c == 'z' && count == 0)
		{
			*p++ = 0;
			*p++ = 0;
			*p++ = 0;
			*p++ = 0;
		}

		else if (c == '~')
		{
			c = fz_read_byte(ctx, state->chain);
			if (c != '>')
				fz_warn(ctx, "bad eod marker in a85d");

			switch (count) {
			case 0:
				break;
			case 1:
				/* Specifically illegal in the spec, but adobe
				 * and gs both cope. See normal_87.pdf for a
				 * case where this matters. */
				fz_warn(ctx, "partial final byte in a85d");
				break;
			case 2:
				word = word * (85 * 85 * 85) + 0xffffff;
				*p++ = word >> 24;
				break;
			case 3:
				word = word * (85 * 85) + 0xffff;
				*p++ = word >> 24;
				*p++ = word >> 16;
				break;
			case 4:
				word = word * 85 + 0xff;
				*p++ = word >> 24;
				*p++ = word >> 16;
				*p++ = word >> 8;
				break;
			}
			state->eod = 1;
			break;
		}

		else if (!iswhite(c))
		{
			fz_throw(ctx, FZ_ERROR_GENERIC, "bad data in a85d: '%c'", c);
		}
	}

	stm->rp = state->buffer;
	stm->wp = p;
	stm->pos += p - state->buffer;

	if (p == stm->rp)
		return EOF;

	return *stm->rp++;
}