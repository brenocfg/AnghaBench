#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  scalar_t__ WNDPROC ;
struct TYPE_17__ {int /*<<< orphan*/  hwndParent; } ;
struct TYPE_16__ {int /*<<< orphan*/  Enabled; TYPE_3__* Part; int /*<<< orphan*/  Notify; int /*<<< orphan*/  Self; } ;
struct TYPE_15__ {int UpperLimit; int /*<<< orphan*/  EditHwnd; scalar_t__ OrigProc; scalar_t__ LowerLimit; } ;
struct TYPE_14__ {int /*<<< orphan*/  lfFaceName; } ;
struct TYPE_13__ {int right; int left; scalar_t__ top; scalar_t__ bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int LRESULT ;
typedef  TYPE_2__ LOGFONTW ;
typedef  TYPE_3__ IPPART_INFO ;
typedef  TYPE_4__ IPADDRESS_INFO ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  TYPE_5__ CREATESTRUCTA ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_VAR_FONT ; 
 scalar_t__ CreateFontIndirectW (TYPE_2__*) ; 
 int /*<<< orphan*/  CreateWindowW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ES_CENTER ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_HINSTANCE ; 
 int /*<<< orphan*/  GWLP_WNDPROC ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetObjectW (scalar_t__,int,TYPE_2__*) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IPADDRESS_SubclassProc ; 
 int /*<<< orphan*/  IPADDRESS_UpdateText (TYPE_4__*) ; 
 int /*<<< orphan*/  IP_SUBCLASS_PROP ; 
 int /*<<< orphan*/  SPI_GETICONTITLELOGFONT ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WC_EDITW ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WS_BORDER ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 TYPE_4__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT IPADDRESS_Create (HWND hwnd, const CREATESTRUCTA *lpCreate)
{
    IPADDRESS_INFO *infoPtr;
    RECT rcClient, edit;
    int i, fieldsize;
    HFONT hFont, hSysFont;
    LOGFONTW logFont, logSysFont;

    TRACE("\n");

    SetWindowLongW (hwnd, GWL_STYLE,
		    GetWindowLongW(hwnd, GWL_STYLE) & ~WS_BORDER);

    infoPtr = heap_alloc_zero (sizeof(*infoPtr));
    if (!infoPtr) return -1;
    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

    GetClientRect (hwnd, &rcClient);

    fieldsize = (rcClient.right - rcClient.left) / 4;

    edit.top    = rcClient.top + 2;
    edit.bottom = rcClient.bottom - 2;

    infoPtr->Self = hwnd;
    infoPtr->Enabled = TRUE;
    infoPtr->Notify = lpCreate->hwndParent;

    hSysFont = GetStockObject(ANSI_VAR_FONT);
    GetObjectW(hSysFont, sizeof(LOGFONTW), &logSysFont);
    SystemParametersInfoW(SPI_GETICONTITLELOGFONT, 0, &logFont, 0);
    strcpyW(logFont.lfFaceName, logSysFont.lfFaceName);
    hFont = CreateFontIndirectW(&logFont);

    for (i = 0; i < 4; i++) {
	IPPART_INFO* part = &infoPtr->Part[i];

	part->LowerLimit = 0;
	part->UpperLimit = 255;
        edit.left = rcClient.left + i*fieldsize + 6;
        edit.right = rcClient.left + (i+1)*fieldsize - 2;
        part->EditHwnd =
		CreateWindowW (WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | ES_CENTER,
                               edit.left, edit.top, edit.right - edit.left,
			       edit.bottom - edit.top, hwnd, (HMENU) 1,
			       (HINSTANCE)GetWindowLongPtrW(hwnd, GWLP_HINSTANCE), NULL);
        SendMessageW(part->EditHwnd, WM_SETFONT, (WPARAM) hFont, FALSE);
	SetPropW(part->EditHwnd, IP_SUBCLASS_PROP, hwnd);
        part->OrigProc = (WNDPROC)
		SetWindowLongPtrW (part->EditHwnd, GWLP_WNDPROC,
				(DWORD_PTR)IPADDRESS_SubclassProc);
        EnableWindow(part->EditHwnd, infoPtr->Enabled);
    }

    IPADDRESS_UpdateText (infoPtr);

    return 0;
}