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
 int /*<<< orphan*/  ASCIIHexDecode ; 
 int /*<<< orphan*/  DecodeParms ; 
 int /*<<< orphan*/  Filter ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_array_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int striphexfilter(fz_context *ctx, pdf_document *doc, pdf_obj *dict)
{
	pdf_obj *f, *dp;
	int is_hex = 0;

	f = pdf_dict_get(ctx, dict, PDF_NAME(Filter));
	dp = pdf_dict_get(ctx, dict, PDF_NAME(DecodeParms));

	if (pdf_is_array(ctx, f))
	{
		/* Remove ASCIIHexDecode from head of filter list */
		if (pdf_array_get(ctx, f, 0) == PDF_NAME(ASCIIHexDecode))
		{
			is_hex = 1;
			pdf_array_delete(ctx, f, 0);
			if (pdf_is_array(ctx, dp))
				pdf_array_delete(ctx, dp, 0);
		}
		/* Unpack array if only one filter remains */
		if (pdf_array_len(ctx, f) == 1)
		{
			f = pdf_array_get(ctx, f, 0);
			pdf_dict_put(ctx, dict, PDF_NAME(Filter), f);
			if (dp)
			{
				dp = pdf_array_get(ctx, dp, 0);
				pdf_dict_put(ctx, dict, PDF_NAME(DecodeParms), dp);
			}
		}
		/* Remove array if no filters remain */
		else if (pdf_array_len(ctx, f) == 0)
		{
			pdf_dict_del(ctx, dict, PDF_NAME(Filter));
			pdf_dict_del(ctx, dict, PDF_NAME(DecodeParms));
		}
	}
	else if (f == PDF_NAME(ASCIIHexDecode))
	{
		is_hex = 1;
		pdf_dict_del(ctx, dict, PDF_NAME(Filter));
		pdf_dict_del(ctx, dict, PDF_NAME(DecodeParms));
	}

	return is_hex;
}