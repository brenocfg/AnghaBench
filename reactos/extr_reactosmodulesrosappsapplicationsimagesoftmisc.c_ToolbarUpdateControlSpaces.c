#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  (* ToolbarChangeControlCallback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;
struct TYPE_4__ {int IsVertical; scalar_t__ HideVertical; scalar_t__ iCommand; int /*<<< orphan*/  hWndControl; } ;
struct TYPE_3__ {int fsStyle; scalar_t__ dwData; } ;
typedef  TYPE_1__ TBBUTTON ;
typedef  TYPE_2__* PTBCUSTCTL ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int CCS_VERT ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TBSTYLE_SEP ; 
 int /*<<< orphan*/  TB_BUTTONCOUNT ; 
 int /*<<< orphan*/  TB_GETBUTTON ; 
 int /*<<< orphan*/  TB_GETSTYLE ; 
 int /*<<< orphan*/  TB_HIDEBUTTON ; 

VOID
ToolbarUpdateControlSpaces(HWND hWndToolbar,
                           ToolbarChangeControlCallback ChangeCallback)
{
    BOOL Vert;
    DWORD nButtons, i;
    TBBUTTON tbtn;

    Vert = ((SendMessage(hWndToolbar,
                         TB_GETSTYLE,
                         0,
                         0) & CCS_VERT) != 0);

    nButtons = (DWORD)SendMessage(hWndToolbar,
                                  TB_BUTTONCOUNT,
                                  0,
                                  0);

    for (i = 0;
         i != nButtons;
         i++)
    {
        if (SendMessage(hWndToolbar,
                        TB_GETBUTTON,
                        (WPARAM)i,
                        (LPARAM)&tbtn))
        {
            if ((tbtn.fsStyle & TBSTYLE_SEP) && tbtn.dwData != 0)
            {
                PTBCUSTCTL cctl = (PTBCUSTCTL)tbtn.dwData;

                cctl->IsVertical = Vert;

                if (cctl->HideVertical)
                {
                    ShowWindow(cctl->hWndControl,
                               (Vert ? SW_HIDE : SW_SHOW));
                    goto ShowHideSep;
                }
                else if (cctl->IsVertical != Vert)
                {
                    ChangeCallback(hWndToolbar,
                                   cctl->hWndControl,
                                   Vert);

ShowHideSep:
                    /* show/hide the separator */
                    SendMessage(hWndToolbar,
                                TB_HIDEBUTTON,
                                (WPARAM)cctl->iCommand,
                                (LPARAM)Vert && cctl->HideVertical);
                }
            }
        }
    }
}