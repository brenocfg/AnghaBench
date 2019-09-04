#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_6__ {int bottom; int top; } ;
struct TYPE_5__ {int cy; int /*<<< orphan*/  cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ RECT ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOZORDER ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WM_GETFONT ; 
 int /*<<< orphan*/  WM_GETTEXT ; 
 int /*<<< orphan*/  WM_GETTEXTLENGTH ; 
 int /*<<< orphan*/  lstrlenW (char*) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int) ; 
 int min (scalar_t__,int) ; 

__attribute__((used)) static void ctrl_resize(HWND hctrl, UINT min_width, UINT max_width, BOOL multiline)
{
    LPWSTR text;
    UINT len, final_width;
    UINT lines, final_height;
    SIZE size;
    RECT rc;
    HDC hdc;
    WCHAR *c;
    HFONT font;

    TRACE("\n");

    len = SendMessageW(hctrl, WM_GETTEXTLENGTH, 0, 0);
    text = HeapAlloc(GetProcessHeap(), 0, sizeof(WCHAR)*(len+1));
    if(!text) return;
    SendMessageW(hctrl, WM_GETTEXT, len+1, (LPARAM)text);

    hdc = GetDC(hctrl);
    font = (HFONT)SendMessageW(hctrl, WM_GETFONT, 0, 0);
    font = SelectObject(hdc, font);
    GetTextExtentPoint32W(hdc, text, lstrlenW(text), &size);
    SelectObject(hdc, font);
    ReleaseDC(hctrl, hdc);

    if(len && multiline)
    {
        /* FIXME: line-wrap */
        for(lines = 1, c = text; *c != '\0'; c++)
            if(*c == '\n') lines++;

        final_height = size.cy*lines + 2*4;
    }
    else
    {
        GetWindowRect(hctrl, &rc);
        final_height = rc.bottom - rc.top;
    }

    final_width = min(max(size.cx, min_width) + 4, max_width);
    SetWindowPos(hctrl, NULL, 0, 0, final_width, final_height,
                 SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

    HeapFree(GetProcessHeap(), 0, text);
}