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
struct rle {int state; int run; int* buf; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  DIFF 131 
#define  ONE 130 
#define  SAME 129 
#define  ZERO 128 
 int /*<<< orphan*/  rle_flush_diff (int /*<<< orphan*/ *,struct rle*) ; 
 int /*<<< orphan*/  rle_flush_same (int /*<<< orphan*/ *,struct rle*) ; 

__attribute__((used)) static void rle_write(fz_context *ctx, void *opaque, const void *data, size_t n)
{
	struct rle *enc = opaque;
	const unsigned char *p = data;
	while (n-- > 0)
	{
		int c = *p++;
		switch (enc->state)
		{
		case ZERO:
			enc->state = ONE;
			enc->run = 1;
			enc->buf[0] = c;
			break;

		case ONE:
			enc->state = DIFF;
			enc->run = 2;
			enc->buf[1] = c;
			break;

		case DIFF:
			/* Max run length */
			if (enc->run == 128)
			{
				rle_flush_diff(ctx, enc);
				enc->state = ONE;
				enc->run = 1;
				enc->buf[0] = c;
			}
			/* Run of three same */
			else if ((enc->run >= 2) && (c == enc->buf[enc->run-1]) && (c == enc->buf[enc->run-2]))
			{
				if (enc->run >= 3) {
					enc->run -= 2; /* skip last two in previous run */
					rle_flush_diff(ctx, enc);
				}
				enc->state = SAME;
				enc->run = 3;
				enc->buf[0] = c;
			}
			else
			{
				enc->buf[enc->run] = c;
				enc->run++;
			}
			break;

		case SAME:
			if ((enc->run == 128) || (c != enc->buf[0]))
			{
				rle_flush_same(ctx, enc);
				enc->state = ONE;
				enc->run = 1;
				enc->buf[0] = c;
			}
			else
			{
				enc->run++;
			}
		}
	}
}