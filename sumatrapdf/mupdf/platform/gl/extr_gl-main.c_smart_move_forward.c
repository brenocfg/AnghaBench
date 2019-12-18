#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_location ;
struct TYPE_2__ {int w; int h; } ;

/* Variables and functions */
 int canvas_h ; 
 int canvas_w ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  currentpage ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  eqloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_next_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ page_tex ; 
 int scroll_x ; 
 int scroll_y ; 

__attribute__((used)) static void smart_move_forward(void)
{
	int slop_x = page_tex.w / 20;
	int slop_y = page_tex.h / 20;
	if (scroll_y + canvas_h >= page_tex.h - slop_y)
	{
		if (scroll_x + canvas_w >= page_tex.w - slop_x)
		{
			fz_location next = fz_next_page(ctx, doc, currentpage);
			if (!eqloc(currentpage, next))
			{
				scroll_x = 0;
				scroll_y = 0;
				currentpage = next;
			}
		}
		else
		{
			scroll_y = 0;
			scroll_x += canvas_w * 9 / 10;
		}
	}
	else
	{
		scroll_y += canvas_h * 9 / 10;
	}
}