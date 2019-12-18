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
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_2__ {scalar_t__ norm_pixel; scalar_t__ back_pixel; } ;

/* Variables and functions */
 scalar_t__ INVALCOLOR ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_set_bg_color (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gui_set_fg_color (int /*<<< orphan*/ *) ; 

void
gui_check_colors()
{
    if (gui.norm_pixel == gui.back_pixel || gui.norm_pixel == INVALCOLOR)
    {
	gui_set_bg_color((char_u *)"White");
	if (gui.norm_pixel == gui.back_pixel || gui.norm_pixel == INVALCOLOR)
	    gui_set_fg_color((char_u *)"Black");
    }
}