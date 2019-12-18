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
struct TYPE_4__ {unsigned char* rp; unsigned char* wp; int /*<<< orphan*/  pos; TYPE_2__* state; } ;
typedef  TYPE_1__ fz_stream ;
struct TYPE_5__ {unsigned char* buffer; int run; int n; void* c; int /*<<< orphan*/  chain; } ;
typedef  TYPE_2__ fz_rld ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 void* fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
next_rld(fz_context *ctx, fz_stream *stm, size_t max)
{
	fz_rld *state = stm->state;
	unsigned char *p = state->buffer;
	unsigned char *ep;

	if (state->run == 128)
		return EOF;

	if (max > sizeof(state->buffer))
		max = sizeof(state->buffer);
	ep = p + max;

	while (p < ep)
	{
		if (state->run == 128)
			break;

		if (state->n == 0)
		{
			state->run = fz_read_byte(ctx, state->chain);
			if (state->run < 0)
			{
				state->run = 128;
				break;
			}
			if (state->run < 128)
				state->n = state->run + 1;
			if (state->run > 128)
			{
				state->n = 257 - state->run;
				state->c = fz_read_byte(ctx, state->chain);
				if (state->c < 0)
					fz_throw(ctx, FZ_ERROR_GENERIC, "premature end of data in run length decode");
			}
		}

		if (state->run < 128)
		{
			while (p < ep && state->n)
			{
				int c = fz_read_byte(ctx, state->chain);
				if (c < 0)
					fz_throw(ctx, FZ_ERROR_GENERIC, "premature end of data in run length decode");
				*p++ = c;
				state->n--;
			}
		}

		if (state->run > 128)
		{
			while (p < ep && state->n)
			{
				*p++ = state->c;
				state->n--;
			}
		}
	}

	stm->rp = state->buffer;
	stm->wp = p;
	stm->pos += p - state->buffer;

	if (p == stm->rp)
		return EOF;

	return *stm->rp++;
}