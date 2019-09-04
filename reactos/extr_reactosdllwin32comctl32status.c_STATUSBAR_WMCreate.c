#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nclm ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_20__ {int /*<<< orphan*/  hwndParent; scalar_t__ lpszName; } ;
struct TYPE_16__ {scalar_t__ idFrom; int /*<<< orphan*/  code; void* hwndFrom; } ;
struct TYPE_19__ {TYPE_3__ hdr; scalar_t__ hwndToolTips; } ;
struct TYPE_18__ {int cbSize; int /*<<< orphan*/  lfStatusFont; } ;
struct TYPE_14__ {scalar_t__ hIcon; scalar_t__ style; scalar_t__ x; scalar_t__ text; void* bound; } ;
struct TYPE_17__ {int numParts; int minHeight; scalar_t__ hwndToolTip; int /*<<< orphan*/  height; TYPE_2__* parts; TYPE_1__ part0; int /*<<< orphan*/  hDefaultFont; int /*<<< orphan*/  Notify; int /*<<< orphan*/  horizontalGap; int /*<<< orphan*/  verticalBorder; int /*<<< orphan*/  horizontalBorder; scalar_t__ hFont; int /*<<< orphan*/  clrBk; int /*<<< orphan*/  simple; void* Self; } ;
struct TYPE_15__ {int x; void* text; scalar_t__ hIcon; scalar_t__ style; void* bound; } ;
typedef  TYPE_4__ STATUS_INFO ;
typedef  int /*<<< orphan*/  STATUSWINDOWPART ;
typedef  void* RECT ;
typedef  TYPE_5__ NONCLIENTMETRICSW ;
typedef  TYPE_6__ NMTOOLTIPSCREATED ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  void* HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  TYPE_7__ CREATESTRUCTA ;

/* Variables and functions */
 void* Alloc (int) ; 
 int /*<<< orphan*/  CLR_DEFAULT ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/  CreateFontIndirectW (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_HINSTANCE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (void*,void**) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowLongPtrW (void*,int /*<<< orphan*/ ) ; 
 int GetWindowLongW (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HORZ_BORDER ; 
 int /*<<< orphan*/  HORZ_GAP ; 
 int /*<<< orphan*/  NF_REQUERY ; 
 int /*<<< orphan*/  NM_TOOLTIPSCREATED ; 
 int /*<<< orphan*/  OpenThemeData (void*,int /*<<< orphan*/ ) ; 
 int SBT_TOOLTIPS ; 
 int /*<<< orphan*/  SM_CYSIZE ; 
 int /*<<< orphan*/  SPI_GETNONCLIENTMETRICS ; 
 int /*<<< orphan*/  STATUSBAR_ComputeHeight (TYPE_4__*) ; 
 int /*<<< orphan*/  STATUSBAR_NotifyFormat (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUSBAR_WMDestroy (TYPE_4__*) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongW (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLTIPS_CLASSW ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int TTS_ALWAYSTIP ; 
 int /*<<< orphan*/  VERT_BORDER ; 
 int /*<<< orphan*/  WM_NOTIFY ; 
 int WS_BORDER ; 
 int WS_POPUP ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_5__*,int) ; 
 int /*<<< orphan*/  strcpyW (void*,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  themeClass ; 

__attribute__((used)) static LRESULT
STATUSBAR_WMCreate (HWND hwnd, const CREATESTRUCTA *lpCreate)
{
    STATUS_INFO *infoPtr;
    NONCLIENTMETRICSW nclm;
    DWORD dwStyle;
    RECT rect;
    int	len;

    TRACE("\n");
    infoPtr = Alloc (sizeof(STATUS_INFO));
    if (!infoPtr) goto create_fail;
    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

    infoPtr->Self = hwnd;
    infoPtr->Notify = lpCreate->hwndParent;
    infoPtr->numParts = 1;
    infoPtr->parts = 0;
    infoPtr->simple = FALSE;
    infoPtr->clrBk = CLR_DEFAULT;
    infoPtr->hFont = 0;
    infoPtr->horizontalBorder = HORZ_BORDER;
    infoPtr->verticalBorder = VERT_BORDER;
    infoPtr->horizontalGap = HORZ_GAP;
    infoPtr->minHeight = GetSystemMetrics(SM_CYSIZE);
    if (infoPtr->minHeight & 1) infoPtr->minHeight--;

    STATUSBAR_NotifyFormat(infoPtr, infoPtr->Notify, NF_REQUERY);

    ZeroMemory (&nclm, sizeof(nclm));
    nclm.cbSize = sizeof(nclm);
    SystemParametersInfoW (SPI_GETNONCLIENTMETRICS, nclm.cbSize, &nclm, 0);
    infoPtr->hDefaultFont = CreateFontIndirectW (&nclm.lfStatusFont);

    GetClientRect (hwnd, &rect);

    /* initialize simple case */
    infoPtr->part0.bound = rect;
    infoPtr->part0.text = 0;
    infoPtr->part0.x = 0;
    infoPtr->part0.style = 0;
    infoPtr->part0.hIcon = 0;

    /* initialize first part */
    infoPtr->parts = Alloc (sizeof(STATUSWINDOWPART));
    if (!infoPtr->parts) goto create_fail;
    infoPtr->parts[0].bound = rect;
    infoPtr->parts[0].text = 0;
    infoPtr->parts[0].x = -1;
    infoPtr->parts[0].style = 0;
    infoPtr->parts[0].hIcon = 0;
    
    OpenThemeData (hwnd, themeClass);

    if (lpCreate->lpszName && (len = strlenW ((LPCWSTR)lpCreate->lpszName)))
    {
        infoPtr->parts[0].text = Alloc ((len + 1)*sizeof(WCHAR));
        if (!infoPtr->parts[0].text) goto create_fail;
        strcpyW (infoPtr->parts[0].text, (LPCWSTR)lpCreate->lpszName);
    }

    dwStyle = GetWindowLongW (hwnd, GWL_STYLE);
    /* native seems to clear WS_BORDER, too */
    dwStyle &= ~WS_BORDER;
    SetWindowLongW (hwnd, GWL_STYLE, dwStyle);

    infoPtr->height = STATUSBAR_ComputeHeight(infoPtr);

    if (dwStyle & SBT_TOOLTIPS) {
	infoPtr->hwndToolTip =
	    CreateWindowExW (0, TOOLTIPS_CLASSW, NULL, WS_POPUP | TTS_ALWAYSTIP,
			     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			     CW_USEDEFAULT, hwnd, 0,
			     (HINSTANCE)GetWindowLongPtrW(hwnd, GWLP_HINSTANCE), NULL);

	if (infoPtr->hwndToolTip) {
	    NMTOOLTIPSCREATED nmttc;

	    nmttc.hdr.hwndFrom = hwnd;
	    nmttc.hdr.idFrom = GetWindowLongPtrW (hwnd, GWLP_ID);
	    nmttc.hdr.code = NM_TOOLTIPSCREATED;
	    nmttc.hwndToolTips = infoPtr->hwndToolTip;

	    SendMessageW (lpCreate->hwndParent, WM_NOTIFY, nmttc.hdr.idFrom, (LPARAM)&nmttc);
	}
    }

    return 0;

create_fail:
    TRACE("    failed!\n");
    if (infoPtr) STATUSBAR_WMDestroy(infoPtr);
    return -1;
}