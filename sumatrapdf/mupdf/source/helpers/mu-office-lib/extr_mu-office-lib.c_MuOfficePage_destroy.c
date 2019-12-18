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
struct TYPE_7__ {int /*<<< orphan*/  ctx; TYPE_1__* pages; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; int /*<<< orphan*/  page; struct TYPE_6__* next; TYPE_2__* doc; } ;
typedef  TYPE_1__ MuOfficePage ;
typedef  TYPE_2__ MuOfficeDoc ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_drop_display_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

void MuOfficePage_destroy(MuOfficePage *page)
{
	MuOfficeDoc *doc;
	MuOfficePage **ptr;

	if (!page)
		return;

	/* Unlink page from doc */
	doc = page->doc;
	ptr = &doc->pages;
	while (*ptr && *ptr != page)
		ptr = &(*ptr)->next;
	assert(*ptr);
	*ptr = page->next;

	fz_drop_page(doc->ctx, page->page);
	fz_drop_display_list(doc->ctx, page->list);
	fz_free(doc->ctx, page);
}