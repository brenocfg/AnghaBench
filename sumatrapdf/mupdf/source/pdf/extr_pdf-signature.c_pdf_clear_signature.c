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
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_2__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  F ; 
 int PDF_ANNOT_IS_LOCKED ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_update_signature_appearance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pdf_clear_signature(fz_context *ctx, pdf_document *doc, pdf_widget *widget)
{
	int flags;

	flags = pdf_dict_get_int(ctx, ((pdf_annot *) widget)->obj, PDF_NAME(F));
	flags &= ~PDF_ANNOT_IS_LOCKED;
	if (flags)
		pdf_dict_put_int(ctx, ((pdf_annot *) widget)->obj, PDF_NAME(F), flags);
	else
		pdf_dict_del(ctx, ((pdf_annot *) widget)->obj, PDF_NAME(F));

	pdf_dict_del(ctx, ((pdf_annot *) widget)->obj, PDF_NAME(V));

	pdf_update_signature_appearance(ctx, widget, NULL, NULL, NULL);
}