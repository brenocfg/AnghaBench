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
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  BS ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  I ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  U ; 
 int /*<<< orphan*/  pdf_dict_putl_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_field_mark_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

void pdf_field_set_border_style(fz_context *ctx, pdf_obj *field, const char *text)
{
	pdf_obj *val;

	if (!strcmp(text, "Solid"))
		val = PDF_NAME(S);
	else if (!strcmp(text, "Dashed"))
		val = PDF_NAME(D);
	else if (!strcmp(text, "Beveled"))
		val = PDF_NAME(B);
	else if (!strcmp(text, "Inset"))
		val = PDF_NAME(I);
	else if (!strcmp(text, "Underline"))
		val = PDF_NAME(U);
	else
		return;

	pdf_dict_putl_drop(ctx, field, val, PDF_NAME(BS), PDF_NAME(S), NULL);
	pdf_field_mark_dirty(ctx, field);
}