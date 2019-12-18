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
struct fmt {int col; int /*<<< orphan*/  indent; scalar_t__ tight; } ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_indent (int /*<<< orphan*/ *,struct fmt*) ; 
 int /*<<< orphan*/  fmt_obj (int /*<<< orphan*/ *,struct fmt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmt_putc (int /*<<< orphan*/ *,struct fmt*,char) ; 
 int /*<<< orphan*/  fmt_sep (int /*<<< orphan*/ *,struct fmt*) ; 
 int /*<<< orphan*/  pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fmt_array(fz_context *ctx, struct fmt *fmt, pdf_obj *obj)
{
	int i, n;

	n = pdf_array_len(ctx, obj);
	if (fmt->tight) {
		fmt_putc(ctx, fmt, '[');
		for (i = 0; i < n; i++) {
			fmt_obj(ctx, fmt, pdf_array_get(ctx, obj, i));
			fmt_sep(ctx, fmt);
		}
		fmt_putc(ctx, fmt, ']');
	}
	else {
		fmt_putc(ctx, fmt, '[');
		fmt->indent ++;
		for (i = 0; i < n; i++) {
			if (fmt->col > 60) {
				fmt_putc(ctx, fmt, '\n');
				fmt_indent(ctx, fmt);
			} else {
				fmt_putc(ctx, fmt, ' ');
			}
			fmt_obj(ctx, fmt, pdf_array_get(ctx, obj, i));
		}
		fmt->indent --;
		fmt_putc(ctx, fmt, ' ');
		fmt_putc(ctx, fmt, ']');
		fmt_sep(ctx, fmt);
	}
}