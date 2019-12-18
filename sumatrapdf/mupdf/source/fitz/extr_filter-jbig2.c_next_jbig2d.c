#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char* rp; unsigned char* wp; int pos; TYPE_2__* state; } ;
typedef  TYPE_1__ fz_stream ;
struct TYPE_6__ {unsigned char* buffer; int idx; TYPE_4__* page; int /*<<< orphan*/  ctx; int /*<<< orphan*/  chain; } ;
typedef  TYPE_2__ fz_jbig2d ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {unsigned char* data; int height; int stride; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 size_t fz_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jbig2_complete_page (int /*<<< orphan*/ ) ; 
 scalar_t__ jbig2_data_in (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 TYPE_4__* jbig2_page_out (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
next_jbig2d(fz_context *ctx, fz_stream *stm, size_t len)
{
	fz_jbig2d *state = stm->state;
	unsigned char tmp[4096];
	unsigned char *buf = state->buffer;
	unsigned char *p = buf;
	unsigned char *ep;
	unsigned char *s;
	int x, w;
	size_t n;

	if (len > sizeof(state->buffer))
		len = sizeof(state->buffer);
	ep = buf + len;

	if (!state->page)
	{
		while (1)
		{
			n = fz_read(ctx, state->chain, tmp, sizeof tmp);
			if (n == 0)
				break;

			if (jbig2_data_in(state->ctx, tmp, n) < 0)
				fz_throw(ctx, FZ_ERROR_GENERIC, "cannot decode jbig2 image");
		}

		if (jbig2_complete_page(state->ctx) < 0)
			fz_throw(ctx, FZ_ERROR_GENERIC, "cannot complete jbig2 image");

		state->page = jbig2_page_out(state->ctx);
		if (!state->page)
			fz_throw(ctx, FZ_ERROR_GENERIC, "no jbig2 image decoded");
	}

	s = state->page->data;
	w = state->page->height * state->page->stride;
	x = state->idx;
	while (p < ep && x < w)
		*p++ = s[x++] ^ 0xff;
	state->idx = x;

	stm->rp = buf;
	stm->wp = p;
	if (p == buf)
		return EOF;
	stm->pos += p - buf;
	return *stm->rp++;
}