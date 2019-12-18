#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  lpCreateParams; } ;
struct TYPE_11__ {TYPE_2__* ActiveBuffer; } ;
struct TYPE_8__ {int /*<<< orphan*/  FontWeight; int /*<<< orphan*/  FontSize; int /*<<< orphan*/  FontFamily; int /*<<< orphan*/  FaceName; } ;
struct TYPE_10__ {scalar_t__ hIcon; int /*<<< orphan*/ * hWindow; int /*<<< orphan*/  hGuiInitEvent; scalar_t__ IsWindowVisible; scalar_t__ hIconSm; int /*<<< orphan*/ * hSysPalette; int /*<<< orphan*/ * hBitmap; int /*<<< orphan*/  hMemDC; TYPE_1__ GuiInfo; int /*<<< orphan*/  hSysMenu; TYPE_4__* Console; } ;
struct TYPE_9__ {int /*<<< orphan*/  ForceCursorOff; int /*<<< orphan*/  CursorBlinkOn; } ;
typedef  TYPE_3__* PGUI_CONSOLE_DATA ;
typedef  TYPE_4__* PCONSRV_CONSOLE ;
typedef  TYPE_5__* LPCREATESTRUCTW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONGUI_UPDATE_TIME ; 
 int /*<<< orphan*/  CONGUI_UPDATE_TIMER ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DragAcceptFiles (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  GetSystemMenu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICON_BIG ; 
 int /*<<< orphan*/  ICON_SMALL ; 
 int /*<<< orphan*/  InitFonts (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtSetEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_NCCREATE ; 
 int /*<<< orphan*/  WM_SETICON ; 
 scalar_t__ ghDefaultIcon ; 

__attribute__((used)) static BOOL
OnNcCreate(HWND hWnd, LPCREATESTRUCTW Create)
{
    PGUI_CONSOLE_DATA GuiData = (PGUI_CONSOLE_DATA)Create->lpCreateParams;
    PCONSRV_CONSOLE Console;

    if (GuiData == NULL)
    {
        DPRINT1("GuiConsoleNcCreate: No GUI data\n");
        return FALSE;
    }

    Console = GuiData->Console;

    GuiData->hWindow = hWnd;
    GuiData->hSysMenu = GetSystemMenu(hWnd, FALSE);

    /* Initialize the fonts */
    if (!InitFonts(GuiData,
                   GuiData->GuiInfo.FaceName,
                   GuiData->GuiInfo.FontFamily,
                   GuiData->GuiInfo.FontSize,
                   GuiData->GuiInfo.FontWeight))
    {
        DPRINT1("GuiConsoleNcCreate: InitFonts failed\n");
        GuiData->hWindow = NULL;
        NtSetEvent(GuiData->hGuiInitEvent, NULL);
        return FALSE;
    }

    /* Initialize the terminal framebuffer */
    GuiData->hMemDC  = CreateCompatibleDC(NULL);
    GuiData->hBitmap = NULL;
    GuiData->hSysPalette = NULL; /* Original system palette */

    /* Update the icons of the window */
    if (GuiData->hIcon != ghDefaultIcon)
    {
        DefWindowProcW(GuiData->hWindow, WM_SETICON, ICON_BIG  , (LPARAM)GuiData->hIcon  );
        DefWindowProcW(GuiData->hWindow, WM_SETICON, ICON_SMALL, (LPARAM)GuiData->hIconSm);
    }

    // FIXME: Keep these instructions here ? ///////////////////////////////////
    Console->ActiveBuffer->CursorBlinkOn = TRUE;
    Console->ActiveBuffer->ForceCursorOff = FALSE;
    ////////////////////////////////////////////////////////////////////////////

    SetWindowLongPtrW(GuiData->hWindow, GWLP_USERDATA, (DWORD_PTR)GuiData);

    if (GuiData->IsWindowVisible)
    {
        SetTimer(GuiData->hWindow, CONGUI_UPDATE_TIMER, CONGUI_UPDATE_TIME, NULL);
    }

    // FIXME: HACK: Potential HACK for CORE-8129; see revision 63595.
    //CreateSysMenu(GuiData->hWindow);

    DPRINT("OnNcCreate - setting start event\n");
    NtSetEvent(GuiData->hGuiInitEvent, NULL);

    /* We accept dropped files */
    DragAcceptFiles(GuiData->hWindow, TRUE);

    return (BOOL)DefWindowProcW(GuiData->hWindow, WM_NCCREATE, 0, (LPARAM)Create);
}