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
typedef  int /*<<< orphan*/  pdf_widget ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int pdf_set_text_field_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int pdf_set_choice_field_value(fz_context *ctx, pdf_widget *widget, const char *new_value)
{
	/* Choice widgets use almost the same keystroke processing as text fields. */
	return pdf_set_text_field_value(ctx, widget, new_value);
}