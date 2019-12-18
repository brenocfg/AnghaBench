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
struct mark {int /*<<< orphan*/  scroll; int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  currentpage ; 
 int /*<<< orphan*/  fz_transform_point_xy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scroll_x ; 
 int /*<<< orphan*/  scroll_y ; 
 int /*<<< orphan*/  view_page_inv_ctm ; 

__attribute__((used)) static struct mark save_mark()
{
	struct mark mark;
	mark.loc = currentpage;
	mark.scroll = fz_transform_point_xy(scroll_x, scroll_y, view_page_inv_ctm);
	return mark;
}