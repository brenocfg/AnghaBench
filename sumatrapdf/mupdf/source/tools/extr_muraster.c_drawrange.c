#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  drawpage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int fz_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* fz_parse_page_range (int /*<<< orphan*/ *,char const*,int*,int*,int) ; 

__attribute__((used)) static void drawrange(fz_context *ctx, fz_document *doc, const char *range)
{
	int page, spage, epage, pagecount;

	pagecount = fz_count_pages(ctx, doc);

	while ((range = fz_parse_page_range(ctx, range, &spage, &epage, pagecount)))
	{
		if (spage < epage)
			for (page = spage; page <= epage; page++)
				drawpage(ctx, doc, page);
		else
			for (page = spage; page >= epage; page--)
				drawpage(ctx, doc, page);
	}
}