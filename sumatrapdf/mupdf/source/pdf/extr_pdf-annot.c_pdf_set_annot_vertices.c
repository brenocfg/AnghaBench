#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_10__ {int /*<<< orphan*/  obj; TYPE_5__* page; } ;
typedef  TYPE_1__ pdf_annot ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ fz_point ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_12__ {int /*<<< orphan*/ * doc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vertices ; 
 int /*<<< orphan*/  check_allowed_subtypes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_invert_matrix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ fz_transform_point (TYPE_2__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_array_push_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dirty_annot (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * pdf_new_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_page_transform (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vertices_subtypes ; 

void
pdf_set_annot_vertices(fz_context *ctx, pdf_annot *annot, int n, const fz_point *v)
{
	pdf_document *doc = annot->page->doc;
	fz_matrix page_ctm, inv_page_ctm;
	pdf_obj *vertices;
	fz_point point;
	int i;

	check_allowed_subtypes(ctx, annot, PDF_NAME(Vertices), vertices_subtypes);
	if (n <= 0 || !v)
		fz_throw(ctx, FZ_ERROR_GENERIC, "invalid number of vertices");

	pdf_page_transform(ctx, annot->page, NULL, &page_ctm);
	inv_page_ctm = fz_invert_matrix(page_ctm);

	vertices = pdf_new_array(ctx, doc, n * 2);
	for (i = 0; i < n; ++i)
	{
		point = fz_transform_point(v[i], inv_page_ctm);
		pdf_array_push_real(ctx, vertices, point.x);
		pdf_array_push_real(ctx, vertices, point.y);
	}
	pdf_dict_put_drop(ctx, annot->obj, PDF_NAME(Vertices), vertices);
	pdf_dirty_annot(ctx, annot);
}