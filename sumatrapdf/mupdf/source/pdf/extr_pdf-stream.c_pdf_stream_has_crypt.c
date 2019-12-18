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
 int /*<<< orphan*/  Crypt ; 
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  Filter ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_geta (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pdf_stream_has_crypt(fz_context *ctx, pdf_obj *stm)
{
	pdf_obj *filters;
	pdf_obj *obj;
	int i;

	filters = pdf_dict_geta(ctx, stm, PDF_NAME(Filter), PDF_NAME(F));
	if (filters)
	{
		if (pdf_name_eq(ctx, filters, PDF_NAME(Crypt)))
			return 1;
		if (pdf_is_array(ctx, filters))
		{
			int n = pdf_array_len(ctx, filters);
			for (i = 0; i < n; i++)
			{
				obj = pdf_array_get(ctx, filters, i);
				if (pdf_name_eq(ctx, obj, PDF_NAME(Crypt)))
					return 1;
			}
		}
	}
	return 0;
}