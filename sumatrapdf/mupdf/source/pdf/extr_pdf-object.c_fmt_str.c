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
struct fmt {int /*<<< orphan*/  gen; int /*<<< orphan*/  num; int /*<<< orphan*/  crypt; } ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_putc (int /*<<< orphan*/ *,struct fmt*,char) ; 
 int /*<<< orphan*/  fmt_str_out ; 
 int /*<<< orphan*/  pdf_encrypt_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fmt*,unsigned char*,int) ; 
 scalar_t__ pdf_to_str_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_to_str_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fmt_str(fz_context *ctx, struct fmt *fmt, pdf_obj *obj)
{
	unsigned char *s = (unsigned char *)pdf_to_str_buf(ctx, obj);
	int n = pdf_to_str_len(ctx, obj);

	fmt_putc(ctx, fmt, '(');
	pdf_encrypt_data(ctx, fmt->crypt, fmt->num, fmt->gen, fmt_str_out, fmt, s, n);
	fmt_putc(ctx, fmt, ')');
}