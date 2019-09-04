#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {TYPE_1__ WindowOrigin; } ;
struct TYPE_10__ {TYPE_2__ GuiInfo; int /*<<< orphan*/  hWindow; } ;
struct TYPE_9__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__* PGUI_CONSOLE_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static VOID
OnMove(PGUI_CONSOLE_DATA GuiData)
{
    RECT rcWnd;

    // TODO: Simplify the code.
    // See: GuiConsoleNotifyWndProc() PM_CREATE_CONSOLE.

    /* Retrieve our real position */
    GetWindowRect(GuiData->hWindow, &rcWnd);
    GuiData->GuiInfo.WindowOrigin.x = rcWnd.left;
    GuiData->GuiInfo.WindowOrigin.y = rcWnd.top;
}