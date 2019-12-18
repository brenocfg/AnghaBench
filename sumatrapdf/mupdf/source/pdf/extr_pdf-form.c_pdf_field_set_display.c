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
#define  Display_Hidden 131 
#define  Display_NoPrint 130 
#define  Display_NoView 129 
#define  Display_Visible 128 
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  Kids ; 
 int PDF_ANNOT_IS_HIDDEN ; 
 int PDF_ANNOT_IS_NO_VIEW ; 
 int PDF_ANNOT_IS_PRINT ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_int (int /*<<< orphan*/ *,int) ; 

void pdf_field_set_display(fz_context *ctx, pdf_obj *field, int d)
{
	pdf_obj *kids = pdf_dict_get(ctx, field, PDF_NAME(Kids));

	if (!kids)
	{
		int mask = (PDF_ANNOT_IS_HIDDEN|PDF_ANNOT_IS_PRINT|PDF_ANNOT_IS_NO_VIEW);
		int f = pdf_dict_get_int(ctx, field, PDF_NAME(F)) & ~mask;
		pdf_obj *fo;

		switch (d)
		{
		case Display_Visible:
			f |= PDF_ANNOT_IS_PRINT;
			break;
		case Display_Hidden:
			f |= PDF_ANNOT_IS_HIDDEN;
			break;
		case Display_NoView:
			f |= (PDF_ANNOT_IS_PRINT|PDF_ANNOT_IS_NO_VIEW);
			break;
		case Display_NoPrint:
			break;
		}

		fo = pdf_new_int(ctx, f);
		pdf_dict_put_drop(ctx, field, PDF_NAME(F), fo);
	}
	else
	{
		int i, n = pdf_array_len(ctx, kids);

		for (i = 0; i < n; i++)
			pdf_field_set_display(ctx, pdf_array_get(ctx, kids, i), d);
	}
}