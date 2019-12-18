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
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  BE ; 
 int /*<<< orphan*/  BS ; 
 int /*<<< orphan*/  Border ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_put_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_dict_put_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  pdf_dirty_annot (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_is_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pdf_set_annot_border(fz_context *ctx, pdf_annot *annot, float w)
{
	pdf_obj *bs = pdf_dict_get(ctx, annot->obj, PDF_NAME(BS));
	if (!pdf_is_dict(ctx, bs))
		bs = pdf_dict_put_dict(ctx, annot->obj, PDF_NAME(BS), 1);
	pdf_dict_put_real(ctx, bs, PDF_NAME(W), w);

	pdf_dict_del(ctx, annot->obj, PDF_NAME(Border)); /* deprecated */
	pdf_dict_del(ctx, annot->obj, PDF_NAME(BE)); /* not supported */

	pdf_dirty_annot(ctx, annot);
}