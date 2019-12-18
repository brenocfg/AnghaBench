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
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_3__ {scalar_t__ x0; scalar_t__ y0; scalar_t__ x1; scalar_t__ y1; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_array_push_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_new_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
intersect_box(fz_context *ctx, pdf_document *doc, pdf_obj *page, pdf_obj *box_name, fz_rect mb)
{
	pdf_obj *box = pdf_dict_get(ctx, page, box_name);
	pdf_obj *newbox;
	fz_rect old_rect;

	if (box == NULL)
		return;

	old_rect.x0 = pdf_array_get_real(ctx, box, 0);
	old_rect.y0 = pdf_array_get_real(ctx, box, 1);
	old_rect.x1 = pdf_array_get_real(ctx, box, 2);
	old_rect.y1 = pdf_array_get_real(ctx, box, 3);

	if (old_rect.x0 < mb.x0)
		old_rect.x0 = mb.x0;
	if (old_rect.y0 < mb.y0)
		old_rect.y0 = mb.y0;
	if (old_rect.x1 > mb.x1)
		old_rect.x1 = mb.x1;
	if (old_rect.y1 > mb.y1)
		old_rect.y1 = mb.y1;

	newbox = pdf_new_array(ctx, doc, 4);
	pdf_array_push_real(ctx, newbox, old_rect.x0);
	pdf_array_push_real(ctx, newbox, old_rect.y0);
	pdf_array_push_real(ctx, newbox, old_rect.x1);
	pdf_array_push_real(ctx, newbox, old_rect.y1);
	pdf_dict_put_drop(ctx, page, box_name, newbox);
}