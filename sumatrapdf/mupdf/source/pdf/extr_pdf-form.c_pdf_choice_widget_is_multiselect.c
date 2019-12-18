#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_widget ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int PDF_CH_FIELD_IS_MULTI_SELECT ; 
#define  PDF_WIDGET_TYPE_LISTBOX 128 
 int pdf_field_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_field_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pdf_choice_widget_is_multiselect(fz_context *ctx, pdf_widget *tw)
{
	pdf_annot *annot = (pdf_annot *)tw;

	if (!annot) return 0;

	switch (pdf_field_type(ctx, annot->obj))
	{
	case PDF_WIDGET_TYPE_LISTBOX:
		return (pdf_field_flags(ctx, annot->obj) & PDF_CH_FIELD_IS_MULTI_SELECT) != 0;
	default:
		return 0;
	}
}