#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_4__ {int dirty; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  AS ; 
 int /*<<< orphan*/  DV ; 
 int /*<<< orphan*/  Kids ; 
 int /*<<< orphan*/  Off ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
#define  PDF_WIDGET_TYPE_BUTTON 131 
#define  PDF_WIDGET_TYPE_CHECKBOX 130 
#define  PDF_WIDGET_TYPE_RADIOBUTTON 129 
#define  PDF_WIDGET_TYPE_SIGNATURE 128 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_field_dirties_document (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_field_mark_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_field_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_form_field(fz_context *ctx, pdf_document *doc, pdf_obj *field)
{
	/* Set V to DV wherever DV is present, and delete V where DV is not.
	 * FIXME: we assume for now that V has not been set unequal
	 * to DV higher in the hierarchy than "field".
	 *
	 * At the bottom of the hierarchy we may find widget annotations
	 * that aren't also fields, but DV and V will not be present in their
	 * dictionaries, and attempts to remove V will be harmless. */
	pdf_obj *dv = pdf_dict_get(ctx, field, PDF_NAME(DV));
	pdf_obj *kids = pdf_dict_get(ctx, field, PDF_NAME(Kids));

	if (dv)
		pdf_dict_put(ctx, field, PDF_NAME(V), dv);
	else
		pdf_dict_del(ctx, field, PDF_NAME(V));

	if (kids == NULL)
	{
		/* The leaves of the tree are widget annotations
		 * In some cases we need to update the appearance state;
		 * in others we need to mark the field as dirty so that
		 * the appearance stream will be regenerated. */
		switch (pdf_field_type(ctx, field))
		{
		case PDF_WIDGET_TYPE_CHECKBOX:
		case PDF_WIDGET_TYPE_RADIOBUTTON:
			{
				pdf_obj *leafv = pdf_dict_get_inheritable(ctx, field, PDF_NAME(V));
				if (!leafv)
					leafv = PDF_NAME(Off);
				pdf_dict_put(ctx, field, PDF_NAME(AS), leafv);
			}
			pdf_field_mark_dirty(ctx, field);
			break;

		case PDF_WIDGET_TYPE_BUTTON:
		case PDF_WIDGET_TYPE_SIGNATURE:
			/* Pushbuttons and signatures have no value to reset. */
			break;

		default:
			pdf_field_mark_dirty(ctx, field);
			break;
		}
	}

	if (pdf_field_dirties_document(ctx, doc, field))
		doc->dirty = 1;
}