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

/* Variables and functions */
 int /*<<< orphan*/  fmt_putc (int /*<<< orphan*/ *,struct fmt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fmt_puts(fz_context *ctx, struct fmt *fmt, char *s)
{
	while (*s)
		fmt_putc(ctx, fmt, *s++);
}