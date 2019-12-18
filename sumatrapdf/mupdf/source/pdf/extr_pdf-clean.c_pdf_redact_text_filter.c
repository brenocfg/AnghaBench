#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_page ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_11__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ pdf_annot ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_quad ;
struct TYPE_12__ {int /*<<< orphan*/  f; int /*<<< orphan*/  e; } ;
typedef  TYPE_2__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QuadPoints ; 
 int /*<<< orphan*/  Rect ; 
 int /*<<< orphan*/  Redact ; 
 int /*<<< orphan*/  Subtype ; 
 TYPE_2__ fz_concat (TYPE_2__,TYPE_2__) ; 
 scalar_t__ fz_is_point_inside_quad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_is_point_inside_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_make_point (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_get_rect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* pdf_first_annot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* pdf_next_annot (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_to_quad (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pdf_redact_text_filter(fz_context *ctx, void *opaque, int *ucsbuf, int ucslen, fz_matrix trm, fz_matrix ctm, fz_rect bbox)
{
	pdf_page *page = opaque;
	pdf_annot *annot;
	pdf_obj *qp;
	fz_rect r;
	fz_quad q;
	int i, n;

	trm = fz_concat(trm, ctm);

	for (annot = pdf_first_annot(ctx, page); annot; annot = pdf_next_annot(ctx, annot))
	{
		if (pdf_dict_get(ctx, annot->obj, PDF_NAME(Subtype)) == PDF_NAME(Redact))
		{
			qp = pdf_dict_get(ctx, annot->obj, PDF_NAME(QuadPoints));
			n = pdf_array_len(ctx, qp);
			if (n > 0)
			{
				for (i = 0; i < n; i += 8)
				{
					q = pdf_to_quad(ctx, qp, i);
					if (fz_is_point_inside_quad(fz_make_point(trm.e, trm.f), q))
						return 1;
				}
			}
			else
			{
				r = pdf_dict_get_rect(ctx, annot->obj, PDF_NAME(Rect));
				if (fz_is_point_inside_rect(fz_make_point(trm.e, trm.f), r))
					return 1;
			}
		}
	}

	return 0;
}