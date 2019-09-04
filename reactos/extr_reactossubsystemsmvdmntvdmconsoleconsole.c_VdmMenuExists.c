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
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetMenuItemCount (int /*<<< orphan*/ ) ; 
 scalar_t__ GetMenuItemID (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ID_CAPTURE_MOUSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VdmMenuPos ; 

__attribute__((used)) static BOOL
VdmMenuExists(HMENU hConsoleMenu)
{
    INT MenuPos, i;
    MenuPos = GetMenuItemCount(hConsoleMenu);

    /* Check for the presence of one of the VDM menu items */
    for (i = 0; i <= MenuPos; i++)
    {
        if (GetMenuItemID(hConsoleMenu, i) == ID_CAPTURE_MOUSE)
        {
            /* Set VdmMenuPos to the position of the existing menu */
            VdmMenuPos = i - 1;
            return TRUE;
        }
    }
    return FALSE;
}