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
struct fmt {scalar_t__ ascii; scalar_t__ crypt; } ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * PDF_FALSE ; 
 int /*<<< orphan*/ * PDF_NULL ; 
 int /*<<< orphan*/ * PDF_TRUE ; 
 int /*<<< orphan*/  fmt_array (int /*<<< orphan*/ *,struct fmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmt_dict (int /*<<< orphan*/ *,struct fmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmt_hex (int /*<<< orphan*/ *,struct fmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmt_name (int /*<<< orphan*/ *,struct fmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmt_puts (int /*<<< orphan*/ *,struct fmt*,char*) ; 
 int /*<<< orphan*/  fmt_str (int /*<<< orphan*/ *,struct fmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ is_binary_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_longer_than_hex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_gen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_to_str_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fmt_obj(fz_context *ctx, struct fmt *fmt, pdf_obj *obj)
{
	char buf[256];

	if (obj == PDF_NULL)
		fmt_puts(ctx, fmt, "null");
	else if (obj == PDF_TRUE)
		fmt_puts(ctx, fmt, "true");
	else if (obj == PDF_FALSE)
		fmt_puts(ctx, fmt, "false");
	else if (pdf_is_indirect(ctx, obj))
	{
		fz_snprintf(buf, sizeof buf, "%d %d R", pdf_to_num(ctx, obj), pdf_to_gen(ctx, obj));
		fmt_puts(ctx, fmt, buf);
	}
	else if (pdf_is_int(ctx, obj))
	{
		fz_snprintf(buf, sizeof buf, "%d", pdf_to_int(ctx, obj));
		fmt_puts(ctx, fmt, buf);
	}
	else if (pdf_is_real(ctx, obj))
	{
		fz_snprintf(buf, sizeof buf, "%g", pdf_to_real(ctx, obj));
		fmt_puts(ctx, fmt, buf);
	}
	else if (pdf_is_string(ctx, obj))
	{
		unsigned char *str = (unsigned char *)pdf_to_str_buf(ctx, obj);
		if (fmt->crypt
			|| (fmt->ascii && is_binary_string(ctx, obj))
			|| (str[0]==0xff && str[1]==0xfe)
			|| (str[0]==0xfe && str[1] == 0xff)
			|| is_longer_than_hex(ctx, obj)
			)
			fmt_hex(ctx, fmt, obj);
		else
			fmt_str(ctx, fmt, obj);
	}
	else if (pdf_is_name(ctx, obj))
		fmt_name(ctx, fmt, obj);
	else if (pdf_is_array(ctx, obj))
		fmt_array(ctx, fmt, obj);
	else if (pdf_is_dict(ctx, obj))
		fmt_dict(ctx, fmt, obj);
	else
		fmt_puts(ctx, fmt, "<unknown object>");
}