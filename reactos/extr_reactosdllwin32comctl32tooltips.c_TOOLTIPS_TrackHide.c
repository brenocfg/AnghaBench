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
struct TYPE_7__ {int /*<<< orphan*/  code; int /*<<< orphan*/  idFrom; int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_6__ {int nTrackTool; int /*<<< orphan*/  hwndSelf; TYPE_1__* tools; } ;
struct TYPE_5__ {int /*<<< orphan*/  uId; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  TYPE_2__ TOOLTIPS_INFO ;
typedef  TYPE_3__ NMHDR ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  HWND_TOP ; 
 int SWP_HIDEWINDOW ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TTN_POP ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static void
TOOLTIPS_TrackHide (const TOOLTIPS_INFO *infoPtr)
{
    TTTOOL_INFO *toolPtr;
    NMHDR hdr;

    TRACE("hide tracking tooltip %d\n", infoPtr->nTrackTool);

    if (infoPtr->nTrackTool == -1)
	return;

    toolPtr = &infoPtr->tools[infoPtr->nTrackTool];

    hdr.hwndFrom = infoPtr->hwndSelf;
    hdr.idFrom = toolPtr->uId;
    hdr.code = TTN_POP;
    SendMessageW (toolPtr->hwnd, WM_NOTIFY, toolPtr->uId, (LPARAM)&hdr);

    SetWindowPos (infoPtr->hwndSelf, HWND_TOP, 0, 0, 0, 0,
		    SWP_NOZORDER | SWP_HIDEWINDOW | SWP_NOACTIVATE);
}