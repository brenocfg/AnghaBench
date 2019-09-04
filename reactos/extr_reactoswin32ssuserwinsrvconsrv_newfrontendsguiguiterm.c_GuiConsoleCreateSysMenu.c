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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  DrawMenuBar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetSystemMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GuiConsoleAppendMenuItems (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GuiConsoleMainMenuItems ; 

__attribute__((used)) static VOID
GuiConsoleCreateSysMenu(HWND hWnd)
{
    HMENU hMenu = GetSystemMenu(hWnd, FALSE);
    if (hMenu != NULL)
    {
        GuiConsoleAppendMenuItems(hMenu, GuiConsoleMainMenuItems);
        DrawMenuBar(hWnd);
    }
}