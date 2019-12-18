#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_6__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  x0; } ;
typedef  TYPE_1__ fz_rect ;
struct TYPE_7__ {int member_0; int member_3; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_2__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_new_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_new_pdf_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__,TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_device *pdf_page_write(fz_context *ctx, pdf_document *doc, fz_rect mediabox, pdf_obj **presources, fz_buffer **pcontents)
{
	fz_matrix pagectm = { 1, 0, 0, -1, -mediabox.x0, mediabox.y1 };
	*presources = pdf_new_dict(ctx, doc, 0);
	*pcontents = fz_new_buffer(ctx, 0);
	return pdf_new_pdf_device(ctx, doc, pagectm, mediabox, *presources, *pcontents);
}