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
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  TU ; 
 int /*<<< orphan*/ * pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* pdf_to_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const char *pdf_field_label(fz_context *ctx, pdf_obj *field)
{
	pdf_obj *label = pdf_dict_get_inheritable(ctx, field, PDF_NAME(TU));
	if (!label)
		label = pdf_dict_get_inheritable(ctx, field, PDF_NAME(T));
	if (label)
		return pdf_to_text_string(ctx, label);
	return "Unnamed";
}