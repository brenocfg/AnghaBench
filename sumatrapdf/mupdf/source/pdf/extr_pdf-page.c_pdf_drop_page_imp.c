#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* doc; int /*<<< orphan*/  obj; int /*<<< orphan*/  widgets; int /*<<< orphan*/  annots; int /*<<< orphan*/  links; } ;
typedef  TYPE_2__ pdf_page ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_annots (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_drop_widgets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_drop_page_imp(fz_context *ctx, pdf_page *page)
{
	fz_drop_link(ctx, page->links);
	pdf_drop_annots(ctx, page->annots);
	pdf_drop_widgets(ctx, page->widgets);

	pdf_drop_obj(ctx, page->obj);

	fz_drop_document(ctx, &page->doc->super);
}