#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_18__ {int /*<<< orphan*/  obj; TYPE_7__* page; } ;
typedef  TYPE_5__ pdf_annot ;
struct TYPE_17__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_16__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_15__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_14__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_19__ {TYPE_4__ lr; TYPE_3__ ll; TYPE_2__ ur; TYPE_1__ ul; } ;
typedef  TYPE_6__ fz_quad ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_20__ {int /*<<< orphan*/ * doc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QuadPoints ; 
 int /*<<< orphan*/  check_allowed_subtypes (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_invert_matrix (int /*<<< orphan*/ ) ; 
 TYPE_6__ fz_transform_quad (TYPE_6__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_array_push_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dirty_annot (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_page_transform (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quad_point_subtypes ; 

void
pdf_add_annot_quad_point(fz_context *ctx, pdf_annot *annot, fz_quad quad)
{
	pdf_document *doc = annot->page->doc;
	fz_matrix page_ctm, inv_page_ctm;
	pdf_obj *quad_points;

	check_allowed_subtypes(ctx, annot, PDF_NAME(QuadPoints), quad_point_subtypes);

	pdf_page_transform(ctx, annot->page, NULL, &page_ctm);
	inv_page_ctm = fz_invert_matrix(page_ctm);

	quad_points = pdf_dict_get(ctx, annot->obj, PDF_NAME(QuadPoints));
	if (!pdf_is_array(ctx, quad_points))
	{
		quad_points = pdf_new_array(ctx, doc, 8);
		pdf_dict_put_drop(ctx, annot->obj, PDF_NAME(QuadPoints), quad_points);
	}

	/* Contrary to the specification, the points within a QuadPoint are NOT ordered
	 * in a counterclockwise fashion. Experiments with Adobe's implementation
	 * indicates a cross-wise ordering is intended: ul, ur, ll, lr.
	 */
	quad = fz_transform_quad(quad, inv_page_ctm);
	pdf_array_push_real(ctx, quad_points, quad.ul.x);
	pdf_array_push_real(ctx, quad_points, quad.ul.y);
	pdf_array_push_real(ctx, quad_points, quad.ur.x);
	pdf_array_push_real(ctx, quad_points, quad.ur.y);
	pdf_array_push_real(ctx, quad_points, quad.ll.x);
	pdf_array_push_real(ctx, quad_points, quad.ll.y);
	pdf_array_push_real(ctx, quad_points, quad.lr.x);
	pdf_array_push_real(ctx, quad_points, quad.lr.y);

	pdf_dirty_annot(ctx, annot);
}