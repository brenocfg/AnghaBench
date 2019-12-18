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

/* Variables and functions */
 int /*<<< orphan*/  gui_resize_shell (int,int) ; 
 int new_pixel_height ; 
 int new_pixel_width ; 

void
gui_may_resize_shell()
{
    int		h, w;

    if (new_pixel_height)
    {
	/* careful: gui_resize_shell() may postpone the resize again if we
	 * were called indirectly by it */
	w = new_pixel_width;
	h = new_pixel_height;
	new_pixel_width = 0;
	new_pixel_height = 0;
	gui_resize_shell(w, h);
    }
}