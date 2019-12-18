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
struct fmt {int dummy; } ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int b ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_putc (int /*<<< orphan*/ *,struct fmt*,int) ; 

__attribute__((used)) static void fmt_hex_out(fz_context *ctx, void *arg, const unsigned char *s, int n)
{
	struct fmt *fmt = (struct fmt *)arg;
	int i, b, c;

	for (i = 0; i < n; i++) {
		b = (unsigned char) s[i];
		c = (b >> 4) & 0x0f;
		fmt_putc(ctx, fmt, c < 0xA ? c + '0' : c + 'A' - 0xA);
		c = (b) & 0x0f;
		fmt_putc(ctx, fmt, c < 0xA ? c + '0' : c + 'A' - 0xA);
	}
}