#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x1; int /*<<< orphan*/  x0; } ;
struct TYPE_8__ {void* doc; TYPE_1__ rect; struct TYPE_8__* next; } ;
typedef  TYPE_2__ fz_link ;
struct TYPE_9__ {scalar_t__* page_margin; int /*<<< orphan*/  page_h; int /*<<< orphan*/  root; } ;
typedef  TYPE_3__ fz_html ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 size_t L ; 
 size_t T ; 
 int /*<<< orphan*/  fz_dirname (char*,char const*,int) ; 
 TYPE_2__* load_link_box (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 

fz_link *
fz_load_html_links(fz_context *ctx, fz_html *html, int page, const char *file, void *doc)
{
	fz_link *link, *head;
	char dir[2048];
	fz_dirname(dir, file, sizeof dir);

	head = load_link_box(ctx, html->root, NULL, page, html->page_h, dir, file);

	for (link = head; link; link = link->next)
	{
		/* Adjust for page margins */
		link->rect.x0 += html->page_margin[L];
		link->rect.x1 += html->page_margin[L];
		link->rect.y0 += html->page_margin[T];
		link->rect.y1 += html->page_margin[T];

		/* Set document pointer */
		link->doc = doc;
	}

	return head;
}