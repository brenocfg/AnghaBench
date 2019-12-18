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
typedef  int /*<<< orphan*/  pdf_obj ;

/* Variables and functions */
 int /*<<< orphan*/  JS ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* pdf_load_stream_or_string_as_utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_print_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * pdf_resolve_indirect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  showtext (char*,int) ; 

__attribute__((used)) static void showaction(pdf_obj *action, const char *name)
{
	if (action)
	{
		pdf_obj *js = pdf_dict_get(ctx, action, PDF_NAME(JS));
		if (js)
		{
			char *src = pdf_load_stream_or_string_as_utf8(ctx, js);
			fz_write_printf(ctx, out, "    %s: {\n", name);
			showtext(src, 1);
			fz_write_printf(ctx, out, "    }\n", name);
			fz_free(ctx, src);
		}
		else
		{
			fz_write_printf(ctx, out, "    %s: ", name);
			if (pdf_is_indirect(ctx, action))
				action = pdf_resolve_indirect(ctx, action);
			pdf_print_obj(ctx, out, action, 1, 1);
			fz_write_printf(ctx, out, "\n");
		}
	}
}