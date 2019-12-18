#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* next_out; int avail_out; scalar_t__ avail_in; int /*<<< orphan*/ * next_in; } ;
struct deflate {TYPE_1__ z; int /*<<< orphan*/  chain; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void deflate_close(fz_context *ctx, void *opaque)
{
	struct deflate *state = opaque;
	unsigned char buffer[32 << 10];
	int err;

	state->z.next_in = NULL;
	state->z.avail_in = 0;
	do
	{
		state->z.next_out = buffer;
		state->z.avail_out = sizeof buffer;
		err = deflate(&state->z, Z_FINISH);
		if (state->z.avail_out > 0)
			fz_write_data(ctx, state->chain, state->z.next_out, state->z.avail_out);
	} while (err == Z_OK);

	if (err != Z_STREAM_END)
		fz_throw(ctx, FZ_ERROR_GENERIC, "zlib compression failed: %d", err);
}