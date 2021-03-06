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
struct fmt {int indent; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_putc (int /*<<< orphan*/ *,struct fmt*,char) ; 

__attribute__((used)) static inline void fmt_indent(fz_context *ctx, struct fmt *fmt)
{
	int i = fmt->indent;
	while (i--) {
		fmt_putc(ctx, fmt, ' ');
		fmt_putc(ctx, fmt, ' ');
	}
}