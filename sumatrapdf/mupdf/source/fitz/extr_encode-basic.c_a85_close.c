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
struct a85 {int /*<<< orphan*/  chain; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  a85_flush (int /*<<< orphan*/ *,struct a85*) ; 
 int /*<<< orphan*/  fz_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void a85_close(fz_context *ctx, void *opaque)
{
	struct a85 *state = opaque;
	a85_flush(ctx, state);
	fz_write_byte(ctx, state->chain, '~');
	fz_write_byte(ctx, state->chain, '>');
}