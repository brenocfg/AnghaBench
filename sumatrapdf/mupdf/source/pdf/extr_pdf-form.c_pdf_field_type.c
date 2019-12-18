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
 int /*<<< orphan*/  Btn ; 
 int /*<<< orphan*/  Ch ; 
 int /*<<< orphan*/  FT ; 
 int PDF_BTN_FIELD_IS_PUSHBUTTON ; 
 int PDF_BTN_FIELD_IS_RADIO ; 
 int PDF_CH_FIELD_IS_COMBO ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int PDF_WIDGET_TYPE_BUTTON ; 
 int PDF_WIDGET_TYPE_CHECKBOX ; 
 int PDF_WIDGET_TYPE_COMBOBOX ; 
 int PDF_WIDGET_TYPE_LISTBOX ; 
 int PDF_WIDGET_TYPE_RADIOBUTTON ; 
 int PDF_WIDGET_TYPE_SIGNATURE ; 
 int PDF_WIDGET_TYPE_TEXT ; 
 int /*<<< orphan*/  Sig ; 
 int /*<<< orphan*/  Tx ; 
 int /*<<< orphan*/ * pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_field_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pdf_field_type(fz_context *ctx, pdf_obj *obj)
{
	pdf_obj *type = pdf_dict_get_inheritable(ctx, obj, PDF_NAME(FT));
	int flags = pdf_field_flags(ctx, obj);
	if (pdf_name_eq(ctx, type, PDF_NAME(Btn)))
	{
		if (flags & PDF_BTN_FIELD_IS_PUSHBUTTON)
			return PDF_WIDGET_TYPE_BUTTON;
		else if (flags & PDF_BTN_FIELD_IS_RADIO)
			return PDF_WIDGET_TYPE_RADIOBUTTON;
		else
			return PDF_WIDGET_TYPE_CHECKBOX;
	}
	else if (pdf_name_eq(ctx, type, PDF_NAME(Tx)))
		return PDF_WIDGET_TYPE_TEXT;
	else if (pdf_name_eq(ctx, type, PDF_NAME(Ch)))
	{
		if (flags & PDF_CH_FIELD_IS_COMBO)
			return PDF_WIDGET_TYPE_COMBOBOX;
		else
			return PDF_WIDGET_TYPE_LISTBOX;
	}
	else if (pdf_name_eq(ctx, type, PDF_NAME(Sig)))
		return PDF_WIDGET_TYPE_SIGNATURE;
	else
		return PDF_WIDGET_TYPE_BUTTON;
}