#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int chapter; int page; } ;
typedef  TYPE_1__ fz_location ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_count_chapter_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int fz_count_chapters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int fz_page_number_from_location(fz_context *ctx, fz_document *doc, fz_location loc)
{
	int i, n, start = 0;
	n = fz_count_chapters(ctx, doc);
	for (i = 0; i < n; ++i)
	{
		if (i == loc.chapter)
			return start + loc.page;
		start += fz_count_chapter_pages(ctx, doc, i);
	}
	return -1;
}