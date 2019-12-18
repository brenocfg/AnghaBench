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
struct TYPE_3__ {int /*<<< orphan*/ * submenu_id; } ;
typedef  TYPE_1__ vimmenu_T ;
typedef  int /*<<< orphan*/  guint32 ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 scalar_t__ GDK_CURRENT_TIME ; 
 int /*<<< orphan*/  GTK_MENU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_menu_popup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* gui_find_menu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  popup_menu_position_func ; 
 int popup_mouse_pos ; 

void
gui_make_popup(char_u *path_name, int mouse_pos)
{
    vimmenu_T *menu;

    popup_mouse_pos = mouse_pos;

    menu = gui_find_menu(path_name);

    if (menu != NULL && menu->submenu_id != NULL)
    {
	gtk_menu_popup(GTK_MENU(menu->submenu_id),
		       NULL, NULL,
		       &popup_menu_position_func, NULL,
		       0U, (guint32)GDK_CURRENT_TIME);
    }
}