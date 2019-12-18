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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  Filter ; 
 int /*<<< orphan*/  JPXDecode ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
pdf_is_jpx_image(fz_context *ctx, pdf_obj *dict)
{
	pdf_obj *filter;
	int i, n;

	filter = pdf_dict_get(ctx, dict, PDF_NAME(Filter));
	if (pdf_name_eq(ctx, filter, PDF_NAME(JPXDecode)))
		return 1;
	n = pdf_array_len(ctx, filter);
	for (i = 0; i < n; i++)
		if (pdf_name_eq(ctx, pdf_array_get(ctx, filter, i), PDF_NAME(JPXDecode)))
			return 1;
	return 0;
}