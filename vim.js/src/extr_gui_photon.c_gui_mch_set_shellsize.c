#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vimWindow; } ;
struct TYPE_4__ {int member_0; int member_1; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ PhDim_t ;

/* Variables and functions */
 int /*<<< orphan*/  PtSetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtWidgetIsRealized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_DIM ; 
 int /*<<< orphan*/  Pt_ARG_MINIMUM_DIM ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_ph_resize_container () ; 
 scalar_t__ pg_margin_bottom ; 
 scalar_t__ pg_margin_left ; 
 scalar_t__ pg_margin_right ; 
 scalar_t__ pg_margin_top ; 

void
gui_mch_set_shellsize(int width, int height,
	int min_width, int min_height, int base_width, int base_height,
	int direction)
{
    PhDim_t window_size = { width, height };
    PhDim_t min_size = { min_width, min_height };

#ifdef USE_PANEL_GROUP
    window_size.w += pg_margin_left + pg_margin_right;
    window_size.h += pg_margin_top + pg_margin_bottom;
#endif

    PtSetResource(gui.vimWindow, Pt_ARG_MINIMUM_DIM, &min_size, 0);
    PtSetResource(gui.vimWindow, Pt_ARG_DIM, &window_size, 0);

    if (! PtWidgetIsRealized(gui.vimWindow))
	gui_ph_resize_container();
}