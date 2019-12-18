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
struct TYPE_8__ {int /*<<< orphan*/  page; int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
struct TYPE_9__ {void* y; void* x; } ;
typedef  TYPE_2__ fz_point ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vertices ; 
 int /*<<< orphan*/  check_allowed_subtypes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ fz_transform_point (TYPE_2__,int /*<<< orphan*/ ) ; 
 void* pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_page_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vertices_subtypes ; 

fz_point
pdf_annot_vertex(fz_context *ctx, pdf_annot *annot, int i)
{
	pdf_obj *vertices;
	fz_matrix page_ctm;
	fz_point point;

	check_allowed_subtypes(ctx, annot, PDF_NAME(Vertices), vertices_subtypes);

	vertices = pdf_dict_get(ctx, annot->obj, PDF_NAME(Vertices));

	pdf_page_transform(ctx, annot->page, NULL, &page_ctm);

	point.x = pdf_array_get_real(ctx, vertices, i * 2);
	point.y = pdf_array_get_real(ctx, vertices, i * 2 + 1);
	return fz_transform_point(point, page_ctm);
}