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
 int vimjs_get_window_height () ; 
 int vimjs_get_window_width () ; 

void
gui_mch_get_screen_dimensions(int *screen_w, int *screen_h)
{
    *screen_w = vimjs_get_window_width();
    *screen_h = vimjs_get_window_height();
}