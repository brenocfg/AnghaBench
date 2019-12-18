#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int chapter; int page; } ;
typedef  TYPE_1__ fz_location ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int fz_count_chapter_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int fz_count_chapters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ fz_make_location (int,int) ; 

fz_location fz_next_page(fz_context *ctx, fz_document *doc, fz_location loc)
{
	int nc = fz_count_chapters(ctx, doc);
	int np = fz_count_chapter_pages(ctx, doc, loc.chapter);
	if (loc.page + 1 == np)
	{
		if (loc.chapter + 1 < nc)
		{
			return fz_make_location(loc.chapter + 1, 0);
		}
	}
	else
	{
		return fz_make_location(loc.chapter, loc.page + 1);
	}
	return loc;
}