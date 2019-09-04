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
typedef  int /*<<< orphan*/  bm ;
struct TYPE_6__ {int /*<<< orphan*/  bmHeight; int /*<<< orphan*/  bmWidth; } ;
struct TYPE_5__ {int /*<<< orphan*/  hbm32bpp; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  scalar_t__ HDC ;
typedef  TYPE_1__ GHOST_DATA ;
typedef  TYPE_2__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CAPTUREBLT ; 
 scalar_t__ CreateCompatibleDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  GetObject (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 TYPE_1__* Ghost_GetData (int /*<<< orphan*/ ) ; 
 int SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Ghost_OnDraw(HWND hwnd, HDC hdc)
{
    BITMAP bm;
    HDC hdcMem;
    GHOST_DATA *pData = Ghost_GetData(hwnd);

    if (!pData || !GetObject(pData->hbm32bpp, sizeof(bm), &bm))
        return;

    hdcMem = CreateCompatibleDC(hdc);
    if (hdcMem)
    {
        HGDIOBJ hbmOld = SelectObject(hdcMem, pData->hbm32bpp);
        BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight,
               hdcMem, 0, 0, SRCCOPY | CAPTUREBLT);
        SelectObject(hdcMem, hbmOld);
        DeleteDC(hdcMem);
    }
}