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
 int /*<<< orphan*/  GM_ADVANCED ; 
 int /*<<< orphan*/  MM_ANISOTROPIC ; 
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
 int /*<<< orphan*/  hbitmap ; 
 int /*<<< orphan*/  hbrush ; 
 int /*<<< orphan*/  hfont ; 
 int /*<<< orphan*/  hpen ; 
 int /*<<< orphan*/  hrgn ; 

__attribute__((used)) static
void
SetSpecialDCState(HDC hdc)
{
    /* Select spcial Objects */
    SelectObject(hdc, hbrush);
    SelectObject(hdc, hpen);
    SelectObject(hdc, hbitmap);
    SelectObject(hdc, hfont);
    SelectObject(hdc, hrgn);

    /* Colors */
    SetDCBrushColor(hdc, RGB(12,34,56));
    SetDCPenColor(hdc, RGB(23,34,45));

    /* Coordinates */
    SetMapMode(hdc, MM_ANISOTROPIC);
    SetGraphicsMode(hdc, GM_ADVANCED);
    SetWindowOrgEx(hdc, 12, 34, NULL);
    SetViewportOrgEx(hdc, 56, 78, NULL);
    SetWindowExtEx(hdc, 123, 456, NULL);
    SetViewportExtEx(hdc, 234, 567, NULL);



}