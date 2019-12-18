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
struct TYPE_4__ {int recalculate; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  AS ; 
 int /*<<< orphan*/  Off ; 
 int PDF_BTN_FIELD_IS_NO_TOGGLE_TO_OFF ; 
 int PDF_BTN_FIELD_IS_RADIO ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/ * find_head_of_field_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_button_field_on_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_field_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_check_grp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void toggle_check_box(fz_context *ctx, pdf_document *doc, pdf_obj *field)
{
	int ff = pdf_field_flags(ctx, field);
	int is_radio = (ff & PDF_BTN_FIELD_IS_RADIO);
	int is_no_toggle_to_off = (ff & PDF_BTN_FIELD_IS_NO_TOGGLE_TO_OFF);
	pdf_obj *grp, *as, *val;

	grp = find_head_of_field_group(ctx, field);
	if (!grp)
		grp = field;

	/* TODO: check V value as well as or instead of AS? */
	as = pdf_dict_get(ctx, field, PDF_NAME(AS));
	if (as && as != PDF_NAME(Off))
	{
		if (is_radio && is_no_toggle_to_off)
			return;
		val = PDF_NAME(Off);
	}
	else
	{
		val = pdf_button_field_on_state(ctx, field);
	}

	pdf_dict_put(ctx, grp, PDF_NAME(V), val);
	set_check_grp(ctx, doc, grp, val);
	doc->recalculate = 1;
}