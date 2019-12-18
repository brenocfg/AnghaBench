#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* drop_page ) (int /*<<< orphan*/ *,TYPE_2__*) ;TYPE_1__* next; TYPE_1__** prev; int /*<<< orphan*/  refs; } ;
typedef  TYPE_2__ fz_page ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {struct TYPE_7__** prev; } ;

/* Variables and functions */
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 

void
fz_drop_page(fz_context *ctx, fz_page *page)
{
	if (fz_drop_imp(ctx, page, &page->refs))
	{
		/* Remove page from the list of open pages */
		if (page->next != NULL)
			page->next->prev = page->prev;
		if (page->prev != NULL)
			*page->prev = page->next;

		if (page->drop_page)
			page->drop_page(ctx, page);

		fz_free(ctx, page);
	}
}