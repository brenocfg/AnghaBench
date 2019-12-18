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
 int /*<<< orphan*/  Opt ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char const* pdf_array_get_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* pdf_to_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const char *pdf_choice_field_option(fz_context *ctx, pdf_obj *field, int export, int i)
{
	pdf_obj *opt = pdf_dict_get_inheritable(ctx, field, PDF_NAME(Opt));
	pdf_obj *ent = pdf_array_get(ctx, opt, i);
	if (pdf_array_len(ctx, ent) == 2)
		return pdf_array_get_text_string(ctx, ent, export ? 0 : 1);
	else
		return pdf_to_text_string(ctx, ent);
}