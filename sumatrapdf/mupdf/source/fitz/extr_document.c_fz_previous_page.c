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
struct TYPE_5__ {int page; scalar_t__ chapter; } ;
typedef  TYPE_1__ fz_location ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int fz_count_chapter_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ fz_make_location (scalar_t__,int) ; 

fz_location fz_previous_page(fz_context *ctx, fz_document *doc, fz_location loc)
{
	if (loc.page == 0)
	{
		if (loc.chapter > 0)
		{
			int np = fz_count_chapter_pages(ctx, doc, loc.chapter - 1);
			return fz_make_location(loc.chapter - 1, np - 1);
		}
	}
	else
	{
		return fz_make_location(loc.chapter, loc.page - 1);
	}
	return loc;
}