#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_8__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ pdf_annot ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ fz_point ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vertices ; 
 int /*<<< orphan*/  check_allowed_subtypes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_invert_matrix (int /*<<< orphan*/ ) ; 
 TYPE_2__ fz_transform_point (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_array_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_new_real (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_page_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vertices_subtypes ; 

void pdf_set_annot_vertex(fz_context *ctx, pdf_annot *annot, int i, fz_point p)
{
	fz_matrix page_ctm, inv_page_ctm;
	pdf_obj *vertices;

	check_allowed_subtypes(ctx, annot, PDF_NAME(Vertices), vertices_subtypes);

	pdf_page_transform(ctx, annot->page, NULL, &page_ctm);
	inv_page_ctm = fz_invert_matrix(page_ctm);

	p = fz_transform_point(p, inv_page_ctm);

	vertices = pdf_dict_get(ctx, annot->obj, PDF_NAME(Vertices));
	pdf_array_put_drop(ctx, vertices, i * 2 + 0, pdf_new_real(ctx, p.x));
	pdf_array_put_drop(ctx, vertices, i * 2 + 1, pdf_new_real(ctx, p.y));
}