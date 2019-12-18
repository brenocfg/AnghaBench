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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILD_TRANSPARENT ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SetWindowTextA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_redraw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pImageList_Draw (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winetest_interactive ; 

__attribute__((used)) static HDC show_image(HWND hwnd, HIMAGELIST himl, int idx, int size,
                      LPCSTR loc, BOOL clear)
{
    HDC hdc;

    if (!winetest_interactive || !himl) return NULL;

    SetWindowTextA(hwnd, loc);
    hdc = GetDC(hwnd);
    pImageList_Draw(himl, idx, hdc, 0, 0, ILD_TRANSPARENT);

    force_redraw(hwnd);

    if (clear)
    {
        BitBlt(hdc, 0, 0, size, size, hdc, size+1, size+1, SRCCOPY);
        ReleaseDC(hwnd, hdc);
        hdc = NULL;
    }

    return hdc;
}