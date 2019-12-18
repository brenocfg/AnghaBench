#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* name; struct TYPE_5__* next; } ;
typedef  TYPE_1__ xps_fixpage ;
struct TYPE_6__ {int /*<<< orphan*/ * last_page; TYPE_1__* first_page; } ;
typedef  TYPE_2__ xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
xps_drop_fixed_pages(fz_context *ctx, xps_document *doc)
{
	xps_fixpage *page = doc->first_page;
	while (page)
	{
		xps_fixpage *next = page->next;
		fz_free(ctx, page->name);
		fz_free(ctx, page);
		page = next;
	}
	doc->first_page = NULL;
	doc->last_page = NULL;
}