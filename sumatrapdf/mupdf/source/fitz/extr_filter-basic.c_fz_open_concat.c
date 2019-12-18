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
struct concat_filter {int max; int pad; int ws_buf; scalar_t__ current; scalar_t__ count; } ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  close_concat ; 
 struct concat_filter* fz_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * fz_new_stream (int /*<<< orphan*/ *,struct concat_filter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_concat ; 

fz_stream *
fz_open_concat(fz_context *ctx, int len, int pad)
{
	struct concat_filter *state;

	state = fz_calloc(ctx, 1, sizeof(struct concat_filter) + (len-1)*sizeof(fz_stream *));
	state->max = len;
	state->count = 0;
	state->current = 0;
	state->pad = pad;
	state->ws_buf = 32;

	return fz_new_stream(ctx, state, next_concat, close_concat);
}