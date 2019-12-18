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
 int /*<<< orphan*/  FT ; 
 int /*<<< orphan*/  Kids ; 
 scalar_t__ PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sig ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  process_field (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_field_hierarchy(fz_context *ctx, pdf_document *doc, pdf_obj *field)
{
	pdf_obj *kids = pdf_dict_get(ctx, field, PDF_NAME(Kids));
	if (kids)
	{
		int i, n;
		n = pdf_array_len(ctx, kids);
		for (i = 0; i < n; ++i)
		{
			pdf_obj *kid = pdf_array_get(ctx, kids, i);
			if (pdf_dict_get_inheritable(ctx, field, PDF_NAME(FT)) == PDF_NAME(Sig))
				process_field_hierarchy(ctx, doc, kid);
		}
	}
	else if (pdf_dict_get_inheritable(ctx, field, PDF_NAME(FT)) == PDF_NAME(Sig))
		process_field(ctx, doc, field);
}