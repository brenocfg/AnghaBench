#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  lpCreateParams; } ;
struct TYPE_16__ {TYPE_2__* ActiveBuffer; } ;
struct TYPE_11__ {int FontFamily; int /*<<< orphan*/  FaceName; int /*<<< orphan*/  FontWeight; int /*<<< orphan*/  FontSize; } ;
struct TYPE_15__ {int /*<<< orphan*/ * hWindow; int /*<<< orphan*/  hGuiInitEvent; int /*<<< orphan*/  CharWidth; scalar_t__ CharHeight; int /*<<< orphan*/ * Font; TYPE_1__ GuiInfo; TYPE_6__* Console; } ;
struct TYPE_14__ {int /*<<< orphan*/  cx; } ;
struct TYPE_13__ {scalar_t__ tmExternalLeading; scalar_t__ tmHeight; int /*<<< orphan*/  tmMaxCharWidth; } ;
struct TYPE_12__ {int /*<<< orphan*/  ForceCursorOff; int /*<<< orphan*/  CursorBlinkOn; } ;
typedef  TYPE_3__ TEXTMETRICW ;
typedef  TYPE_4__ SIZE ;
typedef  TYPE_5__* PGUI_CONSOLE_DATA ;
typedef  TYPE_6__* PCONSOLE ;
typedef  TYPE_7__* LPCREATESTRUCTW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  CONGUI_UPDATE_TIME ; 
 int /*<<< orphan*/  CONGUI_UPDATE_TIMER ; 
 int /*<<< orphan*/ * CreateFontW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int FIXED_PITCH ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 scalar_t__ GetTextExtentPoint32W (int /*<<< orphan*/ *,char*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  GetTextMetricsW (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  GuiConsoleCreateSysMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NONANTIALIASED_QUALITY ; 
 int /*<<< orphan*/  OEM_CHARSET ; 
 int /*<<< orphan*/  OUT_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TA_BASELINE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_NCCREATE ; 

__attribute__((used)) static BOOL
GuiConsoleHandleNcCreate(HWND hWnd, LPCREATESTRUCTW Create)
{
    PGUI_CONSOLE_DATA GuiData = (PGUI_CONSOLE_DATA)Create->lpCreateParams;
    PCONSOLE Console;
    HDC Dc;
    HFONT OldFont;
    TEXTMETRICW Metrics;
    SIZE CharSize;

    DPRINT("GuiConsoleHandleNcCreate\n");

    if (NULL == GuiData)
    {
        DPRINT1("GuiConsoleNcCreate: No GUI data\n");
        return FALSE;
    }

    Console = GuiData->Console;

    GuiData->hWindow = hWnd;

    GuiData->Font = CreateFontW(LOWORD(GuiData->GuiInfo.FontSize),
                                0, // HIWORD(GuiData->GuiInfo.FontSize),
                                0,
                                TA_BASELINE,
                                GuiData->GuiInfo.FontWeight,
                                FALSE,
                                FALSE,
                                FALSE,
                                OEM_CHARSET,
                                OUT_DEFAULT_PRECIS,
                                CLIP_DEFAULT_PRECIS,
                                NONANTIALIASED_QUALITY,
                                FIXED_PITCH | GuiData->GuiInfo.FontFamily /* FF_DONTCARE */,
                                GuiData->GuiInfo.FaceName);

    if (NULL == GuiData->Font)
    {
        DPRINT1("GuiConsoleNcCreate: CreateFont failed\n");
        GuiData->hWindow = NULL;
        SetEvent(GuiData->hGuiInitEvent);
        return FALSE;
    }
    Dc = GetDC(GuiData->hWindow);
    if (NULL == Dc)
    {
        DPRINT1("GuiConsoleNcCreate: GetDC failed\n");
        DeleteObject(GuiData->Font);
        GuiData->hWindow = NULL;
        SetEvent(GuiData->hGuiInitEvent);
        return FALSE;
    }
    OldFont = SelectObject(Dc, GuiData->Font);
    if (NULL == OldFont)
    {
        DPRINT1("GuiConsoleNcCreate: SelectObject failed\n");
        ReleaseDC(GuiData->hWindow, Dc);
        DeleteObject(GuiData->Font);
        GuiData->hWindow = NULL;
        SetEvent(GuiData->hGuiInitEvent);
        return FALSE;
    }
    if (!GetTextMetricsW(Dc, &Metrics))
    {
        DPRINT1("GuiConsoleNcCreate: GetTextMetrics failed\n");
        SelectObject(Dc, OldFont);
        ReleaseDC(GuiData->hWindow, Dc);
        DeleteObject(GuiData->Font);
        GuiData->hWindow = NULL;
        SetEvent(GuiData->hGuiInitEvent);
        return FALSE;
    }
    GuiData->CharWidth  = Metrics.tmMaxCharWidth;
    GuiData->CharHeight = Metrics.tmHeight + Metrics.tmExternalLeading;

    /* Measure real char width more precisely if possible. */
    if (GetTextExtentPoint32W(Dc, L"R", 1, &CharSize))
        GuiData->CharWidth = CharSize.cx;

    SelectObject(Dc, OldFont);

    ReleaseDC(GuiData->hWindow, Dc);

    // FIXME: Keep these instructions here ? ///////////////////////////////////
    Console->ActiveBuffer->CursorBlinkOn = TRUE;
    Console->ActiveBuffer->ForceCursorOff = FALSE;
    ////////////////////////////////////////////////////////////////////////////

    SetWindowLongPtrW(GuiData->hWindow, GWLP_USERDATA, (DWORD_PTR)GuiData);

    SetTimer(GuiData->hWindow, CONGUI_UPDATE_TIMER, CONGUI_UPDATE_TIME, NULL);
    GuiConsoleCreateSysMenu(GuiData->hWindow);

    DPRINT("GuiConsoleHandleNcCreate - setting start event\n");
    SetEvent(GuiData->hGuiInitEvent);

    return (BOOL)DefWindowProcW(GuiData->hWindow, WM_NCCREATE, 0, (LPARAM)Create);
}