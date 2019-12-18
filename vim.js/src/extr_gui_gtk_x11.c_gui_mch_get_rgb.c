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
typedef  unsigned int long_u ;
typedef  scalar_t__ guicolor_T ;
struct TYPE_5__ {int /*<<< orphan*/  drawarea; } ;
struct TYPE_4__ {scalar_t__ blue; scalar_t__ green; scalar_t__ red; } ;
typedef  TYPE_1__ GdkColor ;

/* Variables and functions */
 int /*<<< orphan*/  gdk_colormap_query_color (int /*<<< orphan*/ ,unsigned long,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_widget_get_colormap (int /*<<< orphan*/ ) ; 
 TYPE_2__ gui ; 

long_u
gui_mch_get_rgb(guicolor_T pixel)
{
    GdkColor color;
    gdk_colormap_query_color(gtk_widget_get_colormap(gui.drawarea),
			     (unsigned long)pixel, &color);

    return (((unsigned)color.red   & 0xff00) << 8)
	 |  ((unsigned)color.green & 0xff00)
	 | (((unsigned)color.blue  & 0xff00) >> 8);
}