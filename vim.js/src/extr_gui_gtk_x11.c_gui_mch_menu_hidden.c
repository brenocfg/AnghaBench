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
struct TYPE_3__ {scalar_t__ id; } ;
typedef  TYPE_1__ vimmenu_T ;

/* Variables and functions */
 scalar_t__ GTK_WIDGET_VISIBLE (scalar_t__) ; 
 int /*<<< orphan*/  gtk_widget_hide (scalar_t__) ; 
 int /*<<< orphan*/  gtk_widget_show (scalar_t__) ; 
 int /*<<< orphan*/  gui_mch_update () ; 

void
gui_mch_menu_hidden(vimmenu_T *menu, int hidden)
{
    if (menu->id == 0)
	return;

    if (hidden)
    {
	if (GTK_WIDGET_VISIBLE(menu->id))
	{
	    gtk_widget_hide(menu->id);
	    gui_mch_update();
	}
    }
    else
    {
	if (!GTK_WIDGET_VISIBLE(menu->id))
	{
	    gtk_widget_show(menu->id);
	    gui_mch_update();
	}
    }
}