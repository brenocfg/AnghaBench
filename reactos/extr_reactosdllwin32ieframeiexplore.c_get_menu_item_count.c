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
typedef  int /*<<< orphan*/  item ;
struct TYPE_3__ {int cbSize; int fMask; scalar_t__ hSubMenu; } ;
typedef  TYPE_1__ MENUITEMINFOW ;
typedef  scalar_t__ HMENU ;

/* Variables and functions */
 scalar_t__ GetMenuItemInfoW (scalar_t__,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int MIIM_DATA ; 
 int MIIM_SUBMENU ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static int get_menu_item_count(HMENU menu)
{
    MENUITEMINFOW item;
    int count = 0;
    int i;

    item.cbSize = sizeof(item);
    item.fMask = MIIM_DATA | MIIM_SUBMENU;

    for(i = 0; GetMenuItemInfoW(menu, i, TRUE, &item); i++)
    {
        if(item.hSubMenu)
            count += get_menu_item_count(item.hSubMenu);
        else
            count++;
    }

    return count;
}