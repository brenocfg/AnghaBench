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
 int /*<<< orphan*/  Count ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  Kids ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pages ; 
 int /*<<< orphan*/  Type ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_is_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pdf_count_pages_before_kid(fz_context *ctx, pdf_document *doc, pdf_obj *parent, int kid_num)
{
	pdf_obj *kids = pdf_dict_get(ctx, parent, PDF_NAME(Kids));
	int i, total = 0, len = pdf_array_len(ctx, kids);
	for (i = 0; i < len; i++)
	{
		pdf_obj *kid = pdf_array_get(ctx, kids, i);
		if (pdf_to_num(ctx, kid) == kid_num)
			return total;
		if (pdf_name_eq(ctx, pdf_dict_get(ctx, kid, PDF_NAME(Type)), PDF_NAME(Pages)))
		{
			pdf_obj *count = pdf_dict_get(ctx, kid, PDF_NAME(Count));
			int n = pdf_to_int(ctx, count);
			if (!pdf_is_int(ctx, count) || n < 0)
				fz_throw(ctx, FZ_ERROR_GENERIC, "illegal or missing count in pages tree");
			total += n;
		}
		else
			total++;
	}
	fz_throw(ctx, FZ_ERROR_GENERIC, "kid not found in parent's kids array");
}