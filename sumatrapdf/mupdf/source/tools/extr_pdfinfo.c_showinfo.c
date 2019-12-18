#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  doc; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ globals ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  clearinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* fz_parse_page_range (int /*<<< orphan*/ *,char const*,int*,int*,int) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gatherpageinfo (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  infousage () ; 
 int pdf_count_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printinfo (int /*<<< orphan*/ *,TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void
showinfo(fz_context *ctx, globals *glo, char *filename, int show, const char *pagelist)
{
	int page, spage, epage;
	int allpages;
	int pagecount;
	fz_output *out = glo->out;

	if (!glo->doc)
		infousage();

	allpages = !strcmp(pagelist, "1-N");

	pagecount = pdf_count_pages(ctx, glo->doc);

	while ((pagelist = fz_parse_page_range(ctx, pagelist, &spage, &epage, pagecount)))
	{
		if (allpages)
			fz_write_printf(ctx, out, "Retrieving info from pages %d-%d...\n", spage, epage);
		for (page = spage; page <= epage; page++)
		{
			gatherpageinfo(ctx, glo, page, show);
			if (!allpages)
			{
				fz_write_printf(ctx, out, "Page %d:\n", page);
				printinfo(ctx, glo, filename, show, page);
				fz_write_printf(ctx, out, "\n");
				clearinfo(ctx, glo);
			}
		}
	}

	if (allpages)
		printinfo(ctx, glo, filename, show, -1);
}