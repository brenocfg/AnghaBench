#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int chapter; int number; struct TYPE_10__** prev; struct TYPE_10__* next; int /*<<< orphan*/  incomplete; } ;
typedef  TYPE_1__ fz_page ;
struct TYPE_11__ {TYPE_1__* open; TYPE_1__* (* load_page ) (int /*<<< orphan*/ *,TYPE_2__*,int,int) ;} ;
typedef  TYPE_2__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_ensure_layout (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* fz_keep_page (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* stub1 (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 

fz_page *
fz_load_chapter_page(fz_context *ctx, fz_document *doc, int chapter, int number)
{
	fz_page *page;

	fz_ensure_layout(ctx, doc);

	if (doc)
		for (page = doc->open; page; page = page->next)
			if (page->chapter == chapter && page->number == number)
				return fz_keep_page(ctx, page);

	if (doc && doc->load_page)
	{
		page = doc->load_page(ctx, doc, chapter, number);
		page->chapter = chapter;
		page->number = number;

		/* Insert new page at the head of the list of open pages. */
		if (!page->incomplete)
		{
			if ((page->next = doc->open) != NULL)
				doc->open->prev = &page->next;
			doc->open = page;
			page->prev = &doc->open;
		}
		return page;
	}

	return NULL;
}