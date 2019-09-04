#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* SetWindowRgn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ hthemeScrollbar; scalar_t__ hthemeWindow; int /*<<< orphan*/ * hTabBackgroundBmp; int /*<<< orphan*/ * hTabBackgroundBrush; scalar_t__ HasThemeRgn; } ;
typedef  TYPE_1__* PWND_DATA ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseThemeData (scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 scalar_t__ GetCurrentProcessId () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowThreadProcessId (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ MAKEINTATOM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPropW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atWndContext ; 
 TYPE_2__ g_user32ApiHook ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ThemeDestroyWndData(HWND hWnd)
{
    PWND_DATA pwndData;
    DWORD ProcessId;

    /*Do not destroy WND_DATA of a window that belong to another process */
    GetWindowThreadProcessId(hWnd, &ProcessId);
    if(ProcessId != GetCurrentProcessId())
    {
        return;
    }

    pwndData = (PWND_DATA)GetPropW(hWnd, (LPCWSTR)MAKEINTATOM(atWndContext));
    if(pwndData == NULL)
    {
        return;
    }

    if(pwndData->HasThemeRgn)
    {
        g_user32ApiHook.SetWindowRgn(hWnd, 0, TRUE);
    }

    if (pwndData->hTabBackgroundBrush != NULL)
    {
        CloseThemeData(GetWindowTheme(hWnd));

        DeleteObject(pwndData->hTabBackgroundBrush);
    }

    if (pwndData->hTabBackgroundBmp != NULL)
    {
        DeleteObject(pwndData->hTabBackgroundBmp);
    }

    if (pwndData->hthemeWindow)
    {
        CloseThemeData(pwndData->hthemeWindow);
    }

    if (pwndData->hthemeScrollbar)
    {
        CloseThemeData(pwndData->hthemeScrollbar);
    }

    HeapFree(GetProcessHeap(), 0, pwndData);

    SetPropW( hWnd, (LPCWSTR)MAKEINTATOM(atWndContext), NULL);
}