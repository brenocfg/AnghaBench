#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_14__ {int /*<<< orphan*/  X; int /*<<< orphan*/  Y; } ;
struct TYPE_13__ {int X; int Y; } ;
struct TYPE_12__ {int Y; int X; } ;
struct TYPE_17__ {TYPE_3__ ViewOrigin; TYPE_2__ ViewSize; TYPE_1__ ScreenBufferSize; } ;
struct TYPE_16__ {int /*<<< orphan*/  hWindow; int /*<<< orphan*/  Console; } ;
struct TYPE_15__ {int cbSize; int fMask; int nMax; int nPage; int /*<<< orphan*/  nPos; scalar_t__ nMin; } ;
typedef  TYPE_4__ SCROLLINFO ;
typedef  TYPE_5__* PGUI_CONSOLE_DATA ;
typedef  TYPE_6__* PCONSOLE_SCREEN_BUFFER ;
typedef  int /*<<< orphan*/  PCONSOLE ;
typedef  int DWORD ;

/* Variables and functions */
 TYPE_6__* ConDrvGetActiveScreenBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetScreenBufferSizeUnits (TYPE_6__*,TYPE_5__*,int*,int*) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_VERT ; 
 int SIF_PAGE ; 
 int SIF_POS ; 
 int SIF_RANGE ; 
 int /*<<< orphan*/  SM_CXEDGE ; 
 int /*<<< orphan*/  SM_CXFRAME ; 
 int /*<<< orphan*/  SM_CXVSCROLL ; 
 int /*<<< orphan*/  SM_CYCAPTION ; 
 int /*<<< orphan*/  SM_CYEDGE ; 
 int /*<<< orphan*/  SM_CYFRAME ; 
 int /*<<< orphan*/  SM_CYHSCROLL ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOCOPYBITS ; 
 int SWP_NOMOVE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ShowScrollBar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static VOID
GuiConsoleResizeWindow(PGUI_CONSOLE_DATA GuiData)
{
    PCONSOLE Console = GuiData->Console;
    PCONSOLE_SCREEN_BUFFER Buff = ConDrvGetActiveScreenBuffer(Console);
    SCROLLINFO sInfo;

    DWORD Width, Height;
    UINT  WidthUnit, HeightUnit;

    GetScreenBufferSizeUnits(Buff, GuiData, &WidthUnit, &HeightUnit);

    Width  = Buff->ViewSize.X * WidthUnit  +
             2 * (GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXEDGE));
    Height = Buff->ViewSize.Y * HeightUnit +
             2 * (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYEDGE)) + GetSystemMetrics(SM_CYCAPTION);

    /* Set scrollbar sizes */
    sInfo.cbSize = sizeof(SCROLLINFO);
    sInfo.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    sInfo.nMin = 0;
    if (Buff->ScreenBufferSize.Y > Buff->ViewSize.Y)
    {
        sInfo.nMax  = Buff->ScreenBufferSize.Y - 1;
        sInfo.nPage = Buff->ViewSize.Y;
        sInfo.nPos  = Buff->ViewOrigin.Y;
        SetScrollInfo(GuiData->hWindow, SB_VERT, &sInfo, TRUE);
        Width += GetSystemMetrics(SM_CXVSCROLL);
        ShowScrollBar(GuiData->hWindow, SB_VERT, TRUE);
    }
    else
    {
        ShowScrollBar(GuiData->hWindow, SB_VERT, FALSE);
    }

    if (Buff->ScreenBufferSize.X > Buff->ViewSize.X)
    {
        sInfo.nMax  = Buff->ScreenBufferSize.X - 1;
        sInfo.nPage = Buff->ViewSize.X;
        sInfo.nPos  = Buff->ViewOrigin.X;
        SetScrollInfo(GuiData->hWindow, SB_HORZ, &sInfo, TRUE);
        Height += GetSystemMetrics(SM_CYHSCROLL);
        ShowScrollBar(GuiData->hWindow, SB_HORZ, TRUE);
    }
    else
    {
        ShowScrollBar(GuiData->hWindow, SB_HORZ, FALSE);
    }

    /* Resize the window  */
    SetWindowPos(GuiData->hWindow, NULL, 0, 0, Width, Height,
                 SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOCOPYBITS);
    // NOTE: The SWP_NOCOPYBITS flag can be replaced by a subsequent call
    // to: InvalidateRect(GuiData->hWindow, NULL, TRUE);
}