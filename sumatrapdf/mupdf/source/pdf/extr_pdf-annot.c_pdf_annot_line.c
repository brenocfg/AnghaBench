#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_9__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ pdf_annot ;
struct TYPE_10__ {void* y; void* x; } ;
typedef  TYPE_2__ fz_point ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  L ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_allowed_subtypes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ fz_transform_point (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line_subtypes ; 
 void* pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_page_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pdf_annot_line(fz_context *ctx, pdf_annot *annot, fz_point *a, fz_point *b)
{
	fz_matrix page_ctm;
	pdf_obj *line;

	check_allowed_subtypes(ctx, annot, PDF_NAME(L), line_subtypes);

	pdf_page_transform(ctx, annot->page, NULL, &page_ctm);

	line = pdf_dict_get(ctx, annot->obj, PDF_NAME(L));
	a->x = pdf_array_get_real(ctx, line, 0);
	a->y = pdf_array_get_real(ctx, line, 1);
	b->x = pdf_array_get_real(ctx, line, 2);
	b->y = pdf_array_get_real(ctx, line, 3);
	*a = fz_transform_point(*a, page_ctm);
	*b = fz_transform_point(*b, page_ctm);
}