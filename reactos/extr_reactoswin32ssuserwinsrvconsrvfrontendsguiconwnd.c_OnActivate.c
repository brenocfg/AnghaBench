#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ FullScreen; } ;
struct TYPE_7__ {int /*<<< orphan*/  IgnoreNextMouseSignal; int /*<<< orphan*/  hWindow; TYPE_1__ GuiInfo; } ;
typedef  TYPE_2__* PGUI_CONSOLE_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 int /*<<< orphan*/  EnterFullScreen (TYPE_2__*) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveFullScreen (TYPE_2__*) ; 
 int /*<<< orphan*/  SC_MINIMIZE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WA_ACTIVE ; 
 scalar_t__ WA_CLICKACTIVE ; 
 int /*<<< orphan*/  WM_SYSCOMMAND ; 

__attribute__((used)) static VOID
OnActivate(PGUI_CONSOLE_DATA GuiData, WPARAM wParam)
{
    WORD ActivationState = LOWORD(wParam);

    DPRINT("WM_ACTIVATE - ActivationState = %d\n", ActivationState);

    if ( ActivationState == WA_ACTIVE ||
         ActivationState == WA_CLICKACTIVE )
    {
        if (GuiData->GuiInfo.FullScreen)
        {
            EnterFullScreen(GuiData);
            // // PostMessageW(GuiData->hWindow, WM_SYSCOMMAND, SC_RESTORE, 0);
            // SendMessageW(GuiData->hWindow, WM_SYSCOMMAND, SC_RESTORE, 0);
        }
    }
    else // if (ActivationState == WA_INACTIVE)
    {
        if (GuiData->GuiInfo.FullScreen)
        {
            SendMessageW(GuiData->hWindow, WM_SYSCOMMAND, SC_MINIMIZE, 0);
            LeaveFullScreen(GuiData);
            // // PostMessageW(GuiData->hWindow, WM_SYSCOMMAND, SC_MINIMIZE, 0);
            // SendMessageW(GuiData->hWindow, WM_SYSCOMMAND, SC_MINIMIZE, 0);
        }
    }

    /*
     * Ignore the next mouse signal when we are going to be enabled again via
     * the mouse, in order to prevent, e.g. when we are in Edit mode, erroneous
     * mouse actions from the user that could spoil text selection or copy/pastes.
     */
    if (ActivationState == WA_CLICKACTIVE)
        GuiData->IgnoreNextMouseSignal = TRUE;
}