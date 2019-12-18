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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/ * rp; int /*<<< orphan*/  pos; int /*<<< orphan*/ * wp; TYPE_2__* state; } ;
typedef  TYPE_1__ fz_stream ;
struct TYPE_5__ {int err; int w; int /*<<< orphan*/ * temp; int /*<<< orphan*/  chain; } ;
typedef  TYPE_2__ fz_sgilog24 ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sgilog24val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
next_sgilog24(fz_context *ctx, fz_stream *stm, size_t max)
{
	fz_sgilog24 *state = stm->state;
	uint8_t *p;
	uint8_t *ep;

	(void)max;

	if (state->err)
		return EOF;

	memset(state->temp, 0, state->w * 3);

	p = state->temp;
	ep = p + state->w * 3;
	while (p < ep)
	{
		int c = sgilog24val(ctx, state->chain, p);
		if (c < 0)
		{
			state->err = 1;
			fz_throw(ctx, FZ_ERROR_GENERIC, "premature end of data in run length decode");
		}
		p += 3;
	}

	stm->rp = state->temp;
	stm->wp = p;
	stm->pos += p - stm->rp;

	if (p == stm->rp)
		return EOF;

	return *stm->rp++;
}