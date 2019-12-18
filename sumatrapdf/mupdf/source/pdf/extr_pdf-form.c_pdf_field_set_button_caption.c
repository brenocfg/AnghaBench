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
 int /*<<< orphan*/  CA ; 
 int /*<<< orphan*/  MK ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ PDF_WIDGET_TYPE_BUTTON ; 
 int /*<<< orphan*/  pdf_dict_putl_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_field_mark_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_field_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_text_string (int /*<<< orphan*/ *,char const*) ; 

void pdf_field_set_button_caption(fz_context *ctx, pdf_obj *field, const char *text)
{
	if (pdf_field_type(ctx, field) == PDF_WIDGET_TYPE_BUTTON)
	{
		pdf_obj *val = pdf_new_text_string(ctx, text);
		pdf_dict_putl_drop(ctx, field, val, PDF_NAME(MK), PDF_NAME(CA), NULL);
		pdf_field_mark_dirty(ctx, field);
	}
}