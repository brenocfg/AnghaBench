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
typedef  int /*<<< orphan*/  fz_stream ;
struct TYPE_3__ {struct TYPE_3__* temp; int /*<<< orphan*/ * chain; } ;
typedef  TYPE_1__ fz_sgilog24 ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
close_sgilog24(fz_context *ctx, void *state_)
{
	fz_sgilog24 *state = (fz_sgilog24 *)state_;
	fz_stream *chain = state->chain;

	fz_free(ctx, state->temp);
	fz_free(ctx, state);
	fz_drop_stream(ctx, chain);
}