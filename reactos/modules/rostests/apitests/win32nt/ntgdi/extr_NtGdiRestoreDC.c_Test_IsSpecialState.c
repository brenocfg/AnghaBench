#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x; int y; } ;
struct TYPE_7__ {int cx; int cy; } ;
typedef  TYPE_1__ SIZE ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DC_BRUSH ; 
 int /*<<< orphan*/  DC_PEN ; 
 int /*<<< orphan*/  DEFAULT_BITMAP ; 
 int /*<<< orphan*/  DEFAULT_GUI_FONT ; 
 scalar_t__ GM_ADVANCED ; 
 scalar_t__ GetDCBrushColor (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDCPenColor (int /*<<< orphan*/ ) ; 
 scalar_t__ GetGraphicsMode (int /*<<< orphan*/ ) ; 
 scalar_t__ GetMapMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetViewportExtEx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetViewportOrgEx (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetWindowExtEx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowOrgEx (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ MM_ANISOTROPIC ; 
 scalar_t__ RGB (int,int,int) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST (int) ; 
 scalar_t__ hbitmap ; 
 scalar_t__ hbrush ; 
 scalar_t__ hfont ; 
 scalar_t__ hpen ; 
 int /*<<< orphan*/  hrgn2 ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static
void
Test_IsSpecialState(HDC hdc, BOOL bMemDC)
{
    POINT pt;
    SIZE sz;

    /* Test Objects */
    TEST(SelectObject(hdc, GetStockObject(DC_BRUSH)) == hbrush);
    TEST(SelectObject(hdc, GetStockObject(DC_PEN)) == hpen);
    TEST(SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT)) == hfont);
    if (bMemDC)
    {
        TEST(SelectObject(hdc, GetStockObject(DEFAULT_BITMAP)) == hbitmap);
        TEST(SelectObject(hdc, hrgn2) == (PVOID)1);
    }
    else
    {
        TEST(SelectObject(hdc, GetStockObject(DEFAULT_BITMAP)) == 0);
        TEST(SelectObject(hdc, hrgn2) == (PVOID)2);
    }

    /* Test colors */
    TEST(GetDCBrushColor(hdc) == RGB(12,34,56));
    TEST(GetDCPenColor(hdc) == RGB(23,34,45));

    /* Test coordinates */
    TEST(GetMapMode(hdc) == MM_ANISOTROPIC);
    TEST(GetGraphicsMode(hdc) == GM_ADVANCED);
    GetWindowOrgEx(hdc, &pt);
    TEST(pt.x == 12);
    TEST(pt.y == 34);
    GetViewportOrgEx(hdc, &pt);
    TEST(pt.x == 56);
    TEST(pt.y == 78);
    GetWindowExtEx(hdc, &sz);
    ok(sz.cx == 123, "sz.cx == %ld\n", sz.cx);
    ok(sz.cy == 456, "sz.cy == %ld\n", sz.cy);
    GetViewportExtEx(hdc, &sz);
    TEST(sz.cx == 234);
    TEST(sz.cy == 567);


}