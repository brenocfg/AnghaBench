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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  AS ; 
 int /*<<< orphan*/  Kids ; 
 int /*<<< orphan*/  Off ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pdf_dict_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_name (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void update_checkbox_selector(fz_context *ctx, pdf_document *doc, pdf_obj *field, const char *val)
{
	pdf_obj *kids = pdf_dict_get(ctx, field, PDF_NAME(Kids));

	if (kids)
	{
		int i, n = pdf_array_len(ctx, kids);

		for (i = 0; i < n; i++)
			update_checkbox_selector(ctx, doc, pdf_array_get(ctx, kids, i), val);
	}
	else
	{
		pdf_obj *n = pdf_dict_getp(ctx, field, "AP/N");
		pdf_obj *oval;

		if (pdf_dict_gets(ctx, n, val))
			oval = pdf_new_name(ctx, val);
		else
			oval = PDF_NAME(Off);
		pdf_dict_put_drop(ctx, field, PDF_NAME(AS), oval);
	}
}