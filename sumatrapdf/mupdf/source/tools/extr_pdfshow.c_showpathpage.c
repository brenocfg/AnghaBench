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

/* Variables and functions */
 int /*<<< orphan*/  SEP ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char*,int) ; 
 char* fz_strsep (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isnumber (char*) ; 
 int /*<<< orphan*/  out ; 
 int pdf_count_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_lookup_page_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  showpages () ; 
 int /*<<< orphan*/  showpath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void showpathpage(char *path)
{
	if (path)
	{
		char *part = fz_strsep(&path, SEP);
		if (part && part[0])
		{
			if (!strcmp(part, "*"))
			{
				int i, n;
				char buf[1000];
				n = pdf_count_pages(ctx, doc);
				for (i = 0; i < n; ++i)
				{
					if (path)
					{
						fz_strlcpy(buf, path, sizeof buf);
						showpath(buf, pdf_lookup_page_obj(ctx, doc, i));
					}
					else
						showpath(NULL, pdf_lookup_page_obj(ctx, doc, i));
				}
			}
			else if (isnumber(part))
				showpath(path, pdf_lookup_page_obj(ctx, doc, atoi(part)-1));
			else
				fz_write_string(ctx, out, "null\n");
		}
		else
			fz_write_string(ctx, out, "null\n");
	}
	else
	{
		showpages();
	}
}