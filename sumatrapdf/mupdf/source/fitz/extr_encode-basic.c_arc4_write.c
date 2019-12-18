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
struct arc4 {int /*<<< orphan*/  chain; int /*<<< orphan*/  arc4; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_arc4_encrypt (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static void arc4_write(fz_context *ctx, void *opaque, const void *data, size_t n)
{
	struct arc4 *state = opaque;
	const unsigned char *p = data;
	unsigned char buffer[256];
	while (n > 0)
	{
		size_t x = (n > sizeof buffer) ? sizeof buffer : n;
		fz_arc4_encrypt(&state->arc4, buffer, p, x);
		fz_write_data(ctx, state->chain, buffer, x);
		p += x;
		n -= x;
	}
}