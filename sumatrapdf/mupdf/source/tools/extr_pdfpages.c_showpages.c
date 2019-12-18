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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* fz_parse_page_range (int /*<<< orphan*/ *,char const*,int*,int*,int) ; 
 int /*<<< orphan*/  infousage () ; 
 int pdf_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int showpage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
showpages(fz_context *ctx, pdf_document *doc, fz_output *out, const char *pagelist)
{
	int page, spage, epage;
	int pagecount;
	int ret = 0;

	if (!doc)
		infousage();

	pagecount = pdf_count_pages(ctx, doc);
	while ((pagelist = fz_parse_page_range(ctx, pagelist, &spage, &epage, pagecount)))
	{
		if (spage > epage)
			page = spage, spage = epage, epage = page;
		for (page = spage; page <= epage; page++)
			ret |= showpage(ctx, doc, out, page);
	}

	return ret;
}