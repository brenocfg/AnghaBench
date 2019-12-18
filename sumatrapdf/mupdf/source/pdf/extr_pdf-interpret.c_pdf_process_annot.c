#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* op_Q ) (int /*<<< orphan*/ *,TYPE_1__*) ;int /*<<< orphan*/  (* op_Do_form ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* op_cm ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* op_q ) (int /*<<< orphan*/ *,TYPE_1__*) ;scalar_t__ usage; } ;
typedef  TYPE_1__ pdf_processor ;
typedef  int /*<<< orphan*/  pdf_page ;
struct TYPE_16__ {int /*<<< orphan*/  ocg; } ;
typedef  TYPE_2__ pdf_document ;
struct TYPE_17__ {scalar_t__ ap; int /*<<< orphan*/  obj; } ;
typedef  TYPE_3__ pdf_annot ;
struct TYPE_18__ {int /*<<< orphan*/  f; int /*<<< orphan*/  e; int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
typedef  TYPE_4__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_cookie ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  OC ; 
 int PDF_ANNOT_IS_HIDDEN ; 
 int PDF_ANNOT_IS_INVISIBLE ; 
 int PDF_ANNOT_IS_NO_VIEW ; 
 int PDF_ANNOT_IS_PRINT ; 
 scalar_t__ PDF_ANNOT_POPUP ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 TYPE_4__ pdf_annot_transform (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ pdf_annot_type (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_hidden_ocg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_page_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
pdf_process_annot(fz_context *ctx, pdf_processor *proc, pdf_document *doc, pdf_page *page, pdf_annot *annot, fz_cookie *cookie)
{
	int flags = pdf_dict_get_int(ctx, annot->obj, PDF_NAME(F));

	if (flags & (PDF_ANNOT_IS_INVISIBLE | PDF_ANNOT_IS_HIDDEN))
		return;

	/* popup annotations should never be drawn */
	if (pdf_annot_type(ctx, annot) == PDF_ANNOT_POPUP)
		return;

	if (proc->usage)
	{
		if (!strcmp(proc->usage, "Print") && !(flags & PDF_ANNOT_IS_PRINT))
			return;
		if (!strcmp(proc->usage, "View") && (flags & PDF_ANNOT_IS_NO_VIEW))
			return;
	}

	/* TODO: NoZoom and NoRotate */

	/* XXX what resources, if any, to use for this check? */
	if (pdf_is_hidden_ocg(ctx, doc->ocg, NULL, proc->usage, pdf_dict_get(ctx, annot->obj, PDF_NAME(OC))))
		return;

	if (proc->op_q && proc->op_cm && proc->op_Do_form && proc->op_Q && annot->ap)
	{
		fz_matrix matrix = pdf_annot_transform(ctx, annot);
		proc->op_q(ctx, proc);
		proc->op_cm(ctx, proc,
			matrix.a, matrix.b,
			matrix.c, matrix.d,
			matrix.e, matrix.f);
		proc->op_Do_form(ctx, proc, NULL, annot->ap, pdf_page_resources(ctx, page));
		proc->op_Q(ctx, proc);
	}
}