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
struct a85 {int n; int word; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  a85_flush (int /*<<< orphan*/ *,struct a85*) ; 

__attribute__((used)) static void a85_write(fz_context *ctx, void *opaque, const void *data, size_t n)
{
	struct a85 *state = opaque;
	const unsigned char *p = data;
	while (n-- > 0)
	{
		unsigned int c = *p++;
		if (state->n == 4)
			a85_flush(ctx, state);
		state->word = (state->word << 8) | c;
		state->n++;
	}
}