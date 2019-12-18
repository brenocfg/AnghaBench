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
 int Display_Hidden ; 
 int Display_NoPrint ; 
 int Display_NoView ; 
 int Display_Visible ; 
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  Kids ; 
 int PDF_ANNOT_IS_HIDDEN ; 
 int PDF_ANNOT_IS_NO_VIEW ; 
 int PDF_ANNOT_IS_PRINT ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pdf_field_display(fz_context *ctx, pdf_obj *field)
{
	pdf_obj *kids;
	int f, res = Display_Visible;

	/* Base response on first of children. Not ideal,
	 * but not clear how to handle children with
	 * differing values */
	while ((kids = pdf_dict_get(ctx, field, PDF_NAME(Kids))) != NULL)
		field = pdf_array_get(ctx, kids, 0);

	f = pdf_dict_get_int(ctx, field, PDF_NAME(F));

	if (f & PDF_ANNOT_IS_HIDDEN)
	{
		res = Display_Hidden;
	}
	else if (f & PDF_ANNOT_IS_PRINT)
	{
		if (f & PDF_ANNOT_IS_NO_VIEW)
			res = Display_NoView;
	}
	else
	{
		if (f & PDF_ANNOT_IS_NO_VIEW)
			res = Display_Hidden;
		else
			res = Display_NoPrint;
	}

	return res;
}