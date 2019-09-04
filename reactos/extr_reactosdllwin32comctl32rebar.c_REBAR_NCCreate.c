#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ncm ;
struct TYPE_15__ {scalar_t__ lfWeight; } ;
struct TYPE_14__ {int /*<<< orphan*/  clrBtnFace; int /*<<< orphan*/  clrBtnText; } ;
struct TYPE_13__ {int style; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_12__ {int cbSize; TYPE_9__ lfCaptionFont; } ;
struct TYPE_11__ {int iOldBand; int ichevronhotBand; int iGrabbedBand; int orgStyle; int dwStyle; scalar_t__ hDefaultFont; scalar_t__ hFont; int /*<<< orphan*/  bands; scalar_t__ fStatus; void* hcurDrag; void* hcurVert; void* hcurHorz; void* hcurArrow; int /*<<< orphan*/  DoRedraw; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  clrBtnFace; int /*<<< orphan*/  clrBtnText; void* clrText; void* clrBk; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  TYPE_2__ NONCLIENTMETRICSW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  TYPE_3__ CREATESTRUCTW ;

/* Variables and functions */
 TYPE_1__* Alloc (int) ; 
 int CCS_LAYOUT_MASK ; 
 int CCS_TOP ; 
 void* CLR_NONE ; 
 scalar_t__ CreateFontIndirectW (TYPE_9__*) ; 
 int /*<<< orphan*/  DPA_Create (int) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FW_NORMAL ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDC_ARROW ; 
 scalar_t__ IDC_SIZE ; 
 scalar_t__ IDC_SIZENS ; 
 scalar_t__ IDC_SIZEWE ; 
 void* LoadCursorW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_REQUERY ; 
 TYPE_1__* REBAR_GetInfoPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REBAR_NotifyFormat (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_GETNONCLIENTMETRICS ; 
 int /*<<< orphan*/  SYSTEM_FONT ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_VISIBLE ; 
 TYPE_4__ comctl32_color ; 
 int /*<<< orphan*/  rebar ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
REBAR_NCCreate (HWND hwnd, const CREATESTRUCTW *cs)
{
    REBAR_INFO *infoPtr = REBAR_GetInfoPtr (hwnd);
    RECT wnrc1, clrc1;
    NONCLIENTMETRICSW ncm;
    HFONT tfont;

    if (infoPtr) {
	ERR("Strange info structure pointer *not* NULL\n");
	return FALSE;
    }

    if (TRACE_ON(rebar)) {
	GetWindowRect(hwnd, &wnrc1);
	GetClientRect(hwnd, &clrc1);
        TRACE("window=(%s) client=(%s) cs=(%d,%d %dx%d)\n",
              wine_dbgstr_rect(&wnrc1), wine_dbgstr_rect(&clrc1),
	      cs->x, cs->y, cs->cx, cs->cy);
    }

    /* allocate memory for info structure */
    infoPtr = Alloc (sizeof(REBAR_INFO));
    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

    /* initialize info structure - initial values are 0 */
    infoPtr->clrBk = CLR_NONE;
    infoPtr->clrText = CLR_NONE;
    infoPtr->clrBtnText = comctl32_color.clrBtnText;
    infoPtr->clrBtnFace = comctl32_color.clrBtnFace;
    infoPtr->iOldBand = -1;
    infoPtr->ichevronhotBand = -2;
    infoPtr->iGrabbedBand = -1;
    infoPtr->hwndSelf = hwnd;
    infoPtr->DoRedraw = TRUE;
    infoPtr->hcurArrow = LoadCursorW (0, (LPWSTR)IDC_ARROW);
    infoPtr->hcurHorz  = LoadCursorW (0, (LPWSTR)IDC_SIZEWE);
    infoPtr->hcurVert  = LoadCursorW (0, (LPWSTR)IDC_SIZENS);
    infoPtr->hcurDrag  = LoadCursorW (0, (LPWSTR)IDC_SIZE);
    infoPtr->fStatus = 0;
    infoPtr->hFont = GetStockObject (SYSTEM_FONT);
    infoPtr->bands = DPA_Create(8);

    /* issue WM_NOTIFYFORMAT to get unicode status of parent */
    REBAR_NotifyFormat(infoPtr, NF_REQUERY);

    /* Stow away the original style */
    infoPtr->orgStyle = cs->style;
    /* add necessary styles to the requested styles */
    infoPtr->dwStyle = cs->style | WS_VISIBLE;
    if ((infoPtr->dwStyle & CCS_LAYOUT_MASK) == 0)
        infoPtr->dwStyle |= CCS_TOP;
    SetWindowLongW (hwnd, GWL_STYLE, infoPtr->dwStyle);

    /* get font handle for Caption Font */
    ncm.cbSize = sizeof(ncm);
    SystemParametersInfoW (SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
    /* if the font is bold, set to normal */
    if (ncm.lfCaptionFont.lfWeight > FW_NORMAL) {
	ncm.lfCaptionFont.lfWeight = FW_NORMAL;
    }
    tfont = CreateFontIndirectW (&ncm.lfCaptionFont);
    if (tfont) {
        infoPtr->hFont = infoPtr->hDefaultFont = tfont;
    }

    return TRUE;
}