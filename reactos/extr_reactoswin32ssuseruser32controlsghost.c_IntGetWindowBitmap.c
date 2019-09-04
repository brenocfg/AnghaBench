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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CAPTUREBLT ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IntCreate32BppBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SRCCOPY ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HBITMAP
IntGetWindowBitmap(HWND hwnd, INT cx, INT cy)
{
    HBITMAP hbm = NULL;
    HDC hdc, hdcMem;
    HGDIOBJ hbmOld;

    hdc = GetWindowDC(hwnd);
    if (!hdc)
        return NULL;

    hdcMem = CreateCompatibleDC(hdc);
    if (!hdcMem)
        goto earth;

    hbm = IntCreate32BppBitmap(cx, cy);
    if (hbm)
    {
        hbmOld = SelectObject(hdcMem, hbm);
        BitBlt(hdcMem, 0, 0, cx, cy, hdc, 0, 0, SRCCOPY | CAPTUREBLT);
        SelectObject(hdcMem, hbmOld);
    }

    DeleteDC(hdcMem);

earth:
    ReleaseDC(hwnd, hdc);

    return hbm;
}