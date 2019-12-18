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
struct mark {TYPE_1__ scroll; int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  currentpage ; 
 int /*<<< orphan*/  draw_page_ctm ; 
 TYPE_1__ fz_transform_point (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scroll_x ; 
 int /*<<< orphan*/  scroll_y ; 

__attribute__((used)) static void restore_mark(struct mark mark)
{
	currentpage = mark.loc;
	mark.scroll = fz_transform_point(mark.scroll, draw_page_ctm);
	scroll_x = mark.scroll.x;
	scroll_y = mark.scroll.y;
}