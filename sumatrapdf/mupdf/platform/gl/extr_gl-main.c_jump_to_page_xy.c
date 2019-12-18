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
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ fz_point ;

/* Variables and functions */
 int /*<<< orphan*/  clear_future () ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  currentpage ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  draw_page_ctm ; 
 int /*<<< orphan*/  fz_clamp_location (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_location_from_page_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ fz_transform_point_xy (float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_history () ; 
 int /*<<< orphan*/  scroll_x ; 
 int /*<<< orphan*/  scroll_y ; 

__attribute__((used)) static void jump_to_page_xy(int newpage, float x, float y)
{
	fz_point p = fz_transform_point_xy(x, y, draw_page_ctm);
	clear_future();
	push_history();
	currentpage = fz_location_from_page_number(ctx, doc, newpage);
	currentpage = fz_clamp_location(ctx, doc, currentpage);
	scroll_x = p.x;
	scroll_y = p.y;
	push_history();
}