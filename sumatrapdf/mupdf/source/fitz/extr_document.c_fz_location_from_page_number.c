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
typedef  int /*<<< orphan*/  fz_location ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int fz_count_chapter_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int fz_count_chapters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_make_location (int,int) ; 

fz_location fz_location_from_page_number(fz_context *ctx, fz_document *doc, int number)
{
	int i, m = 0, n = fz_count_chapters(ctx, doc);
	int start = 0;
	if (number < 0)
		number = 0;
	for (i = 0; i < n; ++i)
	{
		m = fz_count_chapter_pages(ctx, doc, i);
		if (number < start + m)
			return fz_make_location(i, number - start);
		start += m;
	}
	return fz_make_location(i-1, m-1);
}