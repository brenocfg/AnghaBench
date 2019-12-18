#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  obj; TYPE_1__* page; } ;
typedef  TYPE_2__ pdf_widget ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int /*<<< orphan*/  doc; } ;

/* Variables and functions */
#define  PDF_WIDGET_TYPE_CHECKBOX 129 
#define  PDF_WIDGET_TYPE_RADIOBUTTON 128 
 int pdf_widget_type (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  toggle_check_box (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pdf_toggle_widget(fz_context *ctx, pdf_widget *widget)
{
	switch (pdf_widget_type(ctx, widget))
	{
	default:
		return 0;
	case PDF_WIDGET_TYPE_CHECKBOX:
	case PDF_WIDGET_TYPE_RADIOBUTTON:
		toggle_check_box(ctx, widget->page->doc, widget->obj);
		return 1;
	}
	return 0;
}