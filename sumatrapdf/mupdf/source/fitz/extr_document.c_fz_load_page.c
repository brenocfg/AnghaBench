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
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int fz_count_chapter_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int fz_count_chapters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_load_chapter_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

fz_page *
fz_load_page(fz_context *ctx, fz_document *doc, int number)
{
	int i, n = fz_count_chapters(ctx, doc);
	int start = 0;
	for (i = 0; i < n; ++i)
	{
		int m = fz_count_chapter_pages(ctx, doc, i);
		if (number < start + m)
			return fz_load_chapter_page(ctx, doc, i, number - start);
		start += m;
	}
	fz_throw(ctx, FZ_ERROR_GENERIC, "Page not found: %d", number+1);
}