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
struct concat_filter {int current; int count; int /*<<< orphan*/ * chain; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,struct concat_filter*) ; 

__attribute__((used)) static void
close_concat(fz_context *ctx, void *state_)
{
	struct concat_filter *state = (struct concat_filter *)state_;
	int i;

	for (i = state->current; i < state->count; i++)
	{
		fz_drop_stream(ctx, state->chain[i]);
	}
	fz_free(ctx, state);
}