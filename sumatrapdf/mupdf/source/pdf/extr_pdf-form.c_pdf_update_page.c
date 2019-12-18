#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_1__ pdf_widget ;
struct TYPE_8__ {TYPE_1__* widgets; TYPE_1__* annots; TYPE_6__* doc; } ;
typedef  TYPE_2__ pdf_page ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {scalar_t__ recalculate; } ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_calculate_form (int /*<<< orphan*/ *,TYPE_6__*) ; 
 scalar_t__ pdf_update_annot (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
pdf_update_page(fz_context *ctx, pdf_page *page)
{
	pdf_annot *annot;
	pdf_widget *widget;
	int changed = 0;

	if (page->doc->recalculate)
		pdf_calculate_form(ctx, page->doc);

	for (annot = page->annots; annot; annot = annot->next)
		if (pdf_update_annot(ctx, annot))
			changed = 1;
	for (widget = page->widgets; widget; widget = widget->next)
		if (pdf_update_annot(ctx, widget))
			changed = 1;

	return changed;
}