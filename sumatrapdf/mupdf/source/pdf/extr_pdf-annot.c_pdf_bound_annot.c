#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* page; int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
struct TYPE_12__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  x0; } ;
typedef  TYPE_2__ fz_rect ;
struct TYPE_13__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ fz_point ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_14__ {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  F ; 
 int PDF_ANNOT_IS_NO_ROTATE ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Rect ; 
 int /*<<< orphan*/  Rotate ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_rotate (int) ; 
 TYPE_3__ fz_transform_point_xy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ fz_transform_rect (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pdf_dict_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ pdf_dict_get_rect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_page_transform (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

fz_rect
pdf_bound_annot(fz_context *ctx, pdf_annot *annot)
{
	fz_matrix page_ctm;
	fz_rect rect;
	int flags;

	rect = pdf_dict_get_rect(ctx, annot->obj, PDF_NAME(Rect));
	pdf_page_transform(ctx, annot->page, NULL, &page_ctm);

	flags = pdf_dict_get_int(ctx, annot->obj, PDF_NAME(F));
	if (flags & PDF_ANNOT_IS_NO_ROTATE)
	{
		int rotate = pdf_to_int(ctx, pdf_dict_get_inheritable(ctx, annot->page->obj, PDF_NAME(Rotate)));
		fz_point tp = fz_transform_point_xy(rect.x0, rect.y1, page_ctm);
		page_ctm = fz_concat(page_ctm, fz_translate(-tp.x, -tp.y));
		page_ctm = fz_concat(page_ctm, fz_rotate(-rotate));
		page_ctm = fz_concat(page_ctm, fz_translate(tp.x, tp.y));
	}

	return fz_transform_rect(rect, page_ctm);
}