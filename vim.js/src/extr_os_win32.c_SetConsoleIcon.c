#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ICON_BIG ; 
 scalar_t__ ICON_SMALL ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETICON ; 

__attribute__((used)) static BOOL
SetConsoleIcon(
    HWND    hWnd,
    HICON   hIconSmall,
    HICON   hIcon)
{
    HICON   hPrevIconSmall;
    HICON   hPrevIcon;

    if (hWnd == NULL)
	return FALSE;

    if (hIconSmall != NULL)
	hPrevIconSmall = (HICON)SendMessage(hWnd, WM_SETICON,
				      (WPARAM)ICON_SMALL, (LPARAM)hIconSmall);
    if (hIcon != NULL)
	hPrevIcon = (HICON)SendMessage(hWnd, WM_SETICON,
					     (WPARAM)ICON_BIG,(LPARAM) hIcon);
    return TRUE;
}