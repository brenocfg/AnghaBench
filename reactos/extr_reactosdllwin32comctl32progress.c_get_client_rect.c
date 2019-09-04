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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetThemeBackgroundContentRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,int,int) ; 
 int PBS_VERTICAL ; 
 int PP_BAR ; 
 int PP_BARVERT ; 

__attribute__((used)) static inline void get_client_rect (HWND hwnd, RECT* rect)
{
    HTHEME theme = GetWindowTheme (hwnd);
    GetClientRect (hwnd, rect);
    if (!theme)
        InflateRect(rect, -1, -1);
    else
    {
        DWORD dwStyle = GetWindowLongW (hwnd, GWL_STYLE);
        int part = (dwStyle & PBS_VERTICAL) ? PP_BARVERT : PP_BAR;
        GetThemeBackgroundContentRect (theme, 0, part, 0, rect, rect);
    }
}