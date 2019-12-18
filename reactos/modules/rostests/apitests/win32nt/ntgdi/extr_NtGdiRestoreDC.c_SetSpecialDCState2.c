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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DC_BRUSH ; 
 int /*<<< orphan*/  DC_PEN ; 
 int /*<<< orphan*/  DEFAULT_BITMAP ; 
 int /*<<< orphan*/  DEFAULT_GUI_FONT ; 
 int /*<<< orphan*/  GM_COMPATIBLE ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MM_ISOTROPIC ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDCBrushColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDCPenColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetGraphicsMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMapMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetViewportExtEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetViewportOrgEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowExtEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowOrgEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrgn2 ; 

__attribute__((used)) static
void
SetSpecialDCState2(HDC hdc)
{
    /* Select spcial Objects */
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SelectObject(hdc, GetStockObject(DC_PEN));
    SelectObject(hdc, GetStockObject(DEFAULT_BITMAP));
    SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
    SelectObject(hdc, hrgn2);

    /* Colors */
    SetDCBrushColor(hdc, RGB(65,43,21));
    SetDCPenColor(hdc, RGB(54,43,32));

    /* Coordinates */
    SetMapMode(hdc, MM_ISOTROPIC);
    SetGraphicsMode(hdc, GM_COMPATIBLE);
    SetWindowOrgEx(hdc, 43, 21, NULL);
    SetViewportOrgEx(hdc, 87, 65, NULL);
    SetWindowExtEx(hdc, 654, 321, NULL);
    SetViewportExtEx(hdc, 765, 432, NULL);


}