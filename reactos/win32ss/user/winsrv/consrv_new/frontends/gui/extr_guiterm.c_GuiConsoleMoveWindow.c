#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {TYPE_1__ WindowOrigin; int /*<<< orphan*/  AutoPosition; } ;
struct TYPE_7__ {TYPE_2__ GuiInfo; int /*<<< orphan*/  hWindow; } ;
typedef  TYPE_3__* PGUI_CONSOLE_DATA ;

/* Variables and functions */
 int SWP_NOACTIVATE ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

VOID
GuiConsoleMoveWindow(PGUI_CONSOLE_DATA GuiData)
{
    /* Move the window if needed (not positioned by the system) */
    if (!GuiData->GuiInfo.AutoPosition)
    {
        SetWindowPos(GuiData->hWindow,
                     NULL,
                     GuiData->GuiInfo.WindowOrigin.x,
                     GuiData->GuiInfo.WindowOrigin.y,
                     0,
                     0,
                     SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}