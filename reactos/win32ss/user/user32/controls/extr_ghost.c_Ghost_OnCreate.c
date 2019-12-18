#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  bDestroyTarget; scalar_t__ hbm32bpp; scalar_t__ hwndTarget; } ;
typedef  TYPE_1__ WCHAR ;
struct TYPE_22__ {scalar_t__ lpCreateParams; } ;
struct TYPE_21__ {scalar_t__ fnid; } ;
struct TYPE_20__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PWND ;
typedef  TYPE_1__* LPWSTR ;
typedef  int LONG_PTR ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HBITMAP ;
typedef  TYPE_1__ GHOST_DATA ;
typedef  int DWORD ;
typedef  TYPE_6__ CREATESTRUCTW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ARRAYSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FNID_GHOST ; 
 int /*<<< orphan*/  GHOST_INTERVAL ; 
 int /*<<< orphan*/  GHOST_PROP ; 
 int /*<<< orphan*/  GHOST_TIMER_ID ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GW_HWNDPREV ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetPropW (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (scalar_t__,TYPE_2__*) ; 
 TYPE_1__* Ghost_GetText (scalar_t__,int*,int) ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDS_NOT_RESPONDING ; 
 scalar_t__ IntGetWindowBitmap (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IntMakeGhostImage (scalar_t__) ; 
 int InternalGetWindowText (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  InvalidateRect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsHungAppWindow (scalar_t__) ; 
 int /*<<< orphan*/  IsWindowVisible (scalar_t__) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  MoveWindow (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtUserSetWindowFNID (scalar_t__,scalar_t__) ; 
 int SWP_DRAWFRAME ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOOWNERZORDER ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SetPropW (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetTimer (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetWindowTextW (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ShowWindowAsync (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCchCatW (TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  User32Instance ; 
 TYPE_3__* ValidateHwnd (scalar_t__) ; 
 int WS_CHILD ; 
 int WS_HSCROLL ; 
 int WS_VISIBLE ; 
 int WS_VSCROLL ; 

__attribute__((used)) static BOOL
Ghost_OnCreate(HWND hwnd, CREATESTRUCTW *lpcs)
{
    HBITMAP hbm32bpp;
    HWND hwndTarget, hwndPrev;
    GHOST_DATA *pData;
    RECT rc;
    DWORD style, exstyle;
    WCHAR szTextW[320], szNotRespondingW[32];
    LPWSTR pszTextW;
    INT cchTextW, cchExtraW, cchNonExtraW;
    PWND pWnd = ValidateHwnd(hwnd);
    if (pWnd)
    {
        if (!pWnd->fnid)
        {
            NtUserSetWindowFNID(hwnd, FNID_GHOST);
        }
        else if (pWnd->fnid != FNID_GHOST)
        {
             ERR("Wrong window class for Ghost! fnId 0x%x\n", pWnd->fnid);
             return FALSE;
        }
    }

    // get the target
    hwndTarget = (HWND)lpcs->lpCreateParams;
    if (!IsWindowVisible(hwndTarget) ||                             // invisible?
        (GetWindowLongPtrW(hwndTarget, GWL_STYLE) & WS_CHILD) ||    // child?
        !IsHungAppWindow(hwndTarget))                               // not hung?
    {
        return FALSE;
    }

    // check prop
    if (GetPropW(hwndTarget, GHOST_PROP))
        return FALSE;

    // set prop
    SetPropW(hwndTarget, GHOST_PROP, hwnd);

    // create user data
    pData = HeapAlloc(GetProcessHeap(), 0, sizeof(GHOST_DATA));
    if (!pData)
    {
        ERR("HeapAlloc failed\n");
        return FALSE;
    }

    // get window image
    GetWindowRect(hwndTarget, &rc);
    hbm32bpp = IntGetWindowBitmap(hwndTarget,
                                  rc.right - rc.left,
                                  rc.bottom - rc.top);
    if (!hbm32bpp)
    {
        ERR("hbm32bpp was NULL\n");
        HeapFree(GetProcessHeap(), 0, pData);
        return FALSE;
    }
    // make a ghost image
    IntMakeGhostImage(hbm32bpp);

    // set user data
    pData->hwndTarget = hwndTarget;
    pData->hbm32bpp = hbm32bpp;
    pData->bDestroyTarget = FALSE;
    SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)pData);

    // get style
    style = GetWindowLongPtrW(hwndTarget, GWL_STYLE);
    exstyle = GetWindowLongPtrW(hwndTarget, GWL_EXSTYLE);

    // get text
    cchTextW = ARRAYSIZE(szTextW);
    cchExtraW = ARRAYSIZE(szNotRespondingW);
    cchNonExtraW = cchTextW - cchExtraW;
    if (InternalGetWindowText(hwndTarget, szTextW,
                              cchNonExtraW) < cchNonExtraW - 1)
    {
        pszTextW = szTextW;
    }
    else
    {
        cchTextW *= 2;
        pszTextW = Ghost_GetText(hwndTarget, &cchTextW, cchExtraW);
        if (!pszTextW)
        {
            ERR("Ghost_GetText failed\n");
            DeleteObject(hbm32bpp);
            HeapFree(GetProcessHeap(), 0, pData);
            return FALSE;
        }
    }

    // don't use scrollbars.
    style &= ~(WS_HSCROLL | WS_VSCROLL | WS_VISIBLE);

    // set style
    SetWindowLongPtrW(hwnd, GWL_STYLE, style);
    SetWindowLongPtrW(hwnd, GWL_EXSTYLE, exstyle);

    // set text with " (Not Responding)"
    LoadStringW(User32Instance, IDS_NOT_RESPONDING,
                szNotRespondingW, ARRAYSIZE(szNotRespondingW));
    StringCchCatW(pszTextW, cchTextW, szNotRespondingW);
    SetWindowTextW(hwnd, pszTextW);

    // free the text buffer
    if (szTextW != pszTextW)
        HeapFree(GetProcessHeap(), 0, pszTextW);

    // get previous window of target
    hwndPrev = GetWindow(hwndTarget, GW_HWNDPREV);

    // hide target
    ShowWindowAsync(hwndTarget, SW_HIDE);

    // shrink the ghost to zero size and insert.
    // this will avoid effects.
    SetWindowPos(hwnd, hwndPrev, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOOWNERZORDER |
                 SWP_DRAWFRAME);

    // resume the position and size of ghost
    MoveWindow(hwnd, rc.left, rc.top,
               rc.right - rc.left, rc.bottom - rc.top, TRUE);

    // make ghost visible
    SetWindowLongPtrW(hwnd, GWL_STYLE, style | WS_VISIBLE);

    // redraw
    InvalidateRect(hwnd, NULL, TRUE);

    // start timer
    SetTimer(hwnd, GHOST_TIMER_ID, GHOST_INTERVAL, NULL);

    return TRUE;
}