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
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRGN ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProcA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ghost_OnDraw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WM_NCPAINT ; 

__attribute__((used)) static void
Ghost_OnNCPaint(HWND hwnd, HRGN hrgn, BOOL bUnicode)
{
    HDC hdc;

    // do the default behaivour
    if (bUnicode)
        DefWindowProcW(hwnd, WM_NCPAINT, (WPARAM)hrgn, 0);
    else
        DefWindowProcA(hwnd, WM_NCPAINT, (WPARAM)hrgn, 0);

    // draw the ghost image
    hdc = GetWindowDC(hwnd);
    if (hdc)
    {
        Ghost_OnDraw(hwnd, hdc);
        ReleaseDC(hwnd, hdc);
    }
}