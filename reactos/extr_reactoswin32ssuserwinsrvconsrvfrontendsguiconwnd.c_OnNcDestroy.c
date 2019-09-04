#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hBitmap; scalar_t__ hMemDC; scalar_t__ IsWindowVisible; } ;
typedef  TYPE_1__* PGUI_CONSOLE_DATA ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CONGUI_UPDATE_TIMER ; 
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteFonts (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  GetSystemMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* GuiGetGuiData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_NCDESTROY ; 

__attribute__((used)) static LRESULT
OnNcDestroy(HWND hWnd)
{
    PGUI_CONSOLE_DATA GuiData = GuiGetGuiData(hWnd);

    /* Free the GuiData registration */
    SetWindowLongPtrW(hWnd, GWLP_USERDATA, (DWORD_PTR)NULL);

    /* Reset the system menu back to default and destroy the previous menu */
    GetSystemMenu(hWnd, TRUE);

    if (GuiData)
    {
        if (GuiData->IsWindowVisible)
            KillTimer(hWnd, CONGUI_UPDATE_TIMER);

        /* Free the terminal framebuffer */
        if (GuiData->hMemDC ) DeleteDC(GuiData->hMemDC);
        if (GuiData->hBitmap) DeleteObject(GuiData->hBitmap);
        // if (GuiData->hSysPalette) DeleteObject(GuiData->hSysPalette);
        DeleteFonts(GuiData);
    }

    return DefWindowProcW(hWnd, WM_NCDESTROY, 0, 0);
}