#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int /*<<< orphan*/  html; TYPE_1__* doc; } ;
typedef  TYPE_2__ epub_page ;
struct TYPE_3__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_html (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
epub_drop_page(fz_context *ctx, fz_page *page_)
{
	epub_page *page = (epub_page *)page_;
	fz_drop_document(ctx, &page->doc->super);
	fz_drop_html(ctx, page->html);
}