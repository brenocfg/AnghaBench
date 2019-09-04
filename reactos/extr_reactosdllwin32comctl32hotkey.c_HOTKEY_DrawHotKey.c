#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_8__ {int /*<<< orphan*/  clrWindow; int /*<<< orphan*/  clrWindowText; int /*<<< orphan*/  clrBtnFace; int /*<<< orphan*/  clrGrayText; } ;
struct TYPE_7__ {scalar_t__ CaretPos; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  hFont; } ;
struct TYPE_6__ {scalar_t__ cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ INT ;
typedef  TYPE_2__ HOTKEY_INFO ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXBORDER ; 
 int /*<<< orphan*/  SM_CYBORDER ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCaretPos (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TextOutW (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WS_DISABLED ; 
 TYPE_3__ comctl32_color ; 

__attribute__((used)) static void
HOTKEY_DrawHotKey(HOTKEY_INFO *infoPtr, HDC hdc, LPCWSTR KeyName, WORD NameLen)
{
    SIZE TextSize;
    INT nXStart, nYStart;
    COLORREF clrOldText, clrOldBk;
    HFONT hFontOld;

    /* Make a gap from the frame */
    nXStart = GetSystemMetrics(SM_CXBORDER);
    nYStart = GetSystemMetrics(SM_CYBORDER);

    hFontOld = SelectObject(hdc, infoPtr->hFont);
    if (GetWindowLongW(infoPtr->hwndSelf, GWL_STYLE) & WS_DISABLED)
    {
        clrOldText = SetTextColor(hdc, comctl32_color.clrGrayText);
        clrOldBk = SetBkColor(hdc, comctl32_color.clrBtnFace);
    }
    else
    {
        clrOldText = SetTextColor(hdc, comctl32_color.clrWindowText);
        clrOldBk = SetBkColor(hdc, comctl32_color.clrWindow);
    }

    TextOutW(hdc, nXStart, nYStart, KeyName, NameLen);

    /* Get the text width for the caret */
    GetTextExtentPoint32W(hdc, KeyName, NameLen, &TextSize);
    infoPtr->CaretPos = nXStart + TextSize.cx;

    SetBkColor(hdc, clrOldBk);
    SetTextColor(hdc, clrOldText);
    SelectObject(hdc, hFontOld);

    /* position the caret */
    SetCaretPos(infoPtr->CaretPos, nYStart);
}