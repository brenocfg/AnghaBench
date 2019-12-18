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
struct fmt {int /*<<< orphan*/  indent; scalar_t__ tight; } ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_indent (int /*<<< orphan*/ *,struct fmt*) ; 
 int /*<<< orphan*/  fmt_obj (int /*<<< orphan*/ *,struct fmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmt_putc (int /*<<< orphan*/ *,struct fmt*,char) ; 
 int /*<<< orphan*/  fmt_puts (int /*<<< orphan*/ *,struct fmt*,char*) ; 
 int /*<<< orphan*/  fmt_sep (int /*<<< orphan*/ *,struct fmt*) ; 
 int /*<<< orphan*/ * pdf_dict_get_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_dict_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fmt_dict(fz_context *ctx, struct fmt *fmt, pdf_obj *obj)
{
	int i, n;
	pdf_obj *key, *val;

	n = pdf_dict_len(ctx, obj);
	if (fmt->tight) {
		fmt_puts(ctx, fmt, "<<");
		for (i = 0; i < n; i++) {
			fmt_obj(ctx, fmt, pdf_dict_get_key(ctx, obj, i));
			fmt_sep(ctx, fmt);
			fmt_obj(ctx, fmt, pdf_dict_get_val(ctx, obj, i));
			fmt_sep(ctx, fmt);
		}
		fmt_puts(ctx, fmt, ">>");
	}
	else {
		fmt_puts(ctx, fmt, "<<\n");
		fmt->indent ++;
		for (i = 0; i < n; i++) {
			key = pdf_dict_get_key(ctx, obj, i);
			val = pdf_dict_get_val(ctx, obj, i);
			fmt_indent(ctx, fmt);
			fmt_obj(ctx, fmt, key);
			fmt_putc(ctx, fmt, ' ');
			if (!pdf_is_indirect(ctx, val) && pdf_is_array(ctx, val))
				fmt->indent ++;
			fmt_obj(ctx, fmt, val);
			fmt_putc(ctx, fmt, '\n');
			if (!pdf_is_indirect(ctx, val) && pdf_is_array(ctx, val))
				fmt->indent --;
		}
		fmt->indent --;
		fmt_indent(ctx, fmt);
		fmt_puts(ctx, fmt, ">>");
	}
}