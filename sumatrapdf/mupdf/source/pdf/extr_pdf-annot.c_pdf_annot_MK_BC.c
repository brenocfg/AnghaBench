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
 int /*<<< orphan*/  BC ; 
 int /*<<< orphan*/  MK ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_annot_color_imp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,float*) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pdf_annot_MK_BC(fz_context *ctx, pdf_annot *annot, int *n, float color[4])
{
	pdf_obj *mk_bc = pdf_dict_get(ctx, pdf_dict_get(ctx, annot->obj, PDF_NAME(MK)), PDF_NAME(BC));
	pdf_annot_color_imp(ctx, mk_bc, n, color);
}