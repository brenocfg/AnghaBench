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
struct TYPE_4__ {int cx; int cy; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetViewportExtEx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowExtEx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MM_ISOTROPIC ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMapMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_SetViewportExt (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  test_SetWindowExt (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void test_isotropic_mapping(void)
{
    SIZE win, vp;
    HDC hdc = GetDC(0);
    
    SetMapMode(hdc, MM_ISOTROPIC);
    
    /* MM_ISOTROPIC is set up like MM_LOMETRIC.
       Initial values after SetMapMode():
       (1 inch = 25.4 mm)
       
                       Windows 9x:               Windows NT:
       Window Ext:     254 x -254                HORZSIZE*10 x VERTSIZE*10
       Viewport Ext:   LOGPIXELSX x LOGPIXELSY   HORZRES x -VERTRES
       
       To test without rounding errors, we have to use multiples of
       these values!
     */
    
    GetWindowExtEx(hdc, &win);
    GetViewportExtEx(hdc, &vp);
    
    test_SetViewportExt(hdc, 10 * vp.cx, 10 * vp.cy, 10 * vp.cx, 10 * vp.cy);
    test_SetWindowExt(hdc, win.cx, win.cy, 10 * vp.cx, 10 * vp.cy);
    test_SetWindowExt(hdc, 2 * win.cx, win.cy, 10 * vp.cx, 5 * vp.cy);
    test_SetWindowExt(hdc, win.cx, win.cy, 5 * vp.cx, 5 * vp.cy);
    test_SetViewportExt(hdc, 4 * vp.cx, 2 * vp.cy, 2 * vp.cx, 2 * vp.cy);
    test_SetViewportExt(hdc, vp.cx, 2 * vp.cy, vp.cx, vp.cy);
    test_SetViewportExt(hdc, 2 * vp.cx, 2 * vp.cy, 2 * vp.cx, 2 * vp.cy);
    test_SetViewportExt(hdc, 4 * vp.cx, 2 * vp.cy, 2 * vp.cx, 2 * vp.cy);
    test_SetWindowExt(hdc, 4 * win.cx, 2 * win.cy, 2 * vp.cx, vp.cy);
    test_SetViewportExt(hdc, -2 * vp.cx, -4 * vp.cy, -2 * vp.cx, -vp.cy);
    test_SetViewportExt(hdc, -2 * vp.cx, -1 * vp.cy, -2 * vp.cx, -vp.cy);    
    test_SetWindowExt(hdc, -4 * win.cx, -2 * win.cy, -2 * vp.cx, -vp.cy);
    test_SetWindowExt(hdc, 4 * win.cx, -4 * win.cy, -vp.cx, -vp.cy);
    
    ReleaseDC(0, hdc);
}