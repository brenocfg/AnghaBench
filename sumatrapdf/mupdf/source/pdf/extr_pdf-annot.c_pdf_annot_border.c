#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_3__ {int /*<<< orphan*/ * obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  BS ; 
 int /*<<< orphan*/  Border ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float pdf_to_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

float
pdf_annot_border(fz_context *ctx, pdf_annot *annot)
{
	pdf_obj *bs, *bs_w, *border;
	bs = pdf_dict_get(ctx, annot->obj, PDF_NAME(BS));
	bs_w = pdf_dict_get(ctx, bs, PDF_NAME(W));
	if (pdf_is_number(ctx, bs_w))
		return pdf_to_real(ctx, bs_w);
	border = pdf_dict_get(ctx, annot->obj, PDF_NAME(Border));
	bs_w = pdf_array_get(ctx, border, 2);
	if (pdf_is_number(ctx, bs_w))
		return pdf_to_real(ctx, bs_w);
	return 1;
}