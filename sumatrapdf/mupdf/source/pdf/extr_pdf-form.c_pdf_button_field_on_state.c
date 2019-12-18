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
 int /*<<< orphan*/  AP ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  N ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Yes ; 
 int /*<<< orphan*/ * find_on_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

pdf_obj *pdf_button_field_on_state(fz_context *ctx, pdf_obj *field)
{
	pdf_obj *ap = pdf_dict_get(ctx, field, PDF_NAME(AP));
	pdf_obj *on = find_on_state(ctx, pdf_dict_get(ctx, ap, PDF_NAME(N)));
	if (!on) on = find_on_state(ctx, pdf_dict_get(ctx, ap, PDF_NAME(D)));
	if (!on) on = PDF_NAME(Yes);
	return on;
}