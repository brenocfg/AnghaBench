#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
struct TYPE_3__ {scalar_t__ tmHeight; } ;
typedef  TYPE_1__ TEXTMETRICA ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCX_CACHE ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ GetCurrentObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDCEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextMetricsA (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LBS_OWNERDRAWVARIABLE ; 
 int /*<<< orphan*/  LB_GETITEMHEIGHT ; 
 int /*<<< orphan*/  OBJ_FONT ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_LISTBOXA ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int /*<<< orphan*/  create_listbox (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_item_height(void)
{
    INT itemHeight;
    TEXTMETRICA tm;
    HFONT font;
    HWND hLB;
    HDC hdc;

    hLB = create_listbox (0, 0);
    ok ((hdc = GetDCEx( hLB, 0, DCX_CACHE )) != 0, "Can't get hdc\n");
    ok ((font = GetCurrentObject(hdc, OBJ_FONT)) != 0, "Can't get the current font\n");
    ok (GetTextMetricsA( hdc, &tm ), "Can't read font metrics\n");
    ReleaseDC( hLB, hdc);

    ok (SendMessageA(hLB, WM_SETFONT, (WPARAM)font, 0) == 0, "Can't set font\n");

    itemHeight = SendMessageA(hLB, LB_GETITEMHEIGHT, 0, 0);
    ok (itemHeight == tm.tmHeight, "Item height wrong, got %d, expecting %d\n", itemHeight, tm.tmHeight);

    DestroyWindow (hLB);

    hLB = CreateWindowA(WC_LISTBOXA, "TestList", LBS_OWNERDRAWVARIABLE,  0, 0, 100, 100, NULL, NULL, NULL, 0);

    itemHeight = SendMessageA(hLB, LB_GETITEMHEIGHT, 0, 0);
    ok(itemHeight > 0 && itemHeight <= tm.tmHeight, "Unexpected item height %d, expected %d.\n",
        itemHeight, tm.tmHeight);
    itemHeight = SendMessageA(hLB, LB_GETITEMHEIGHT, 5, 0);
    ok(itemHeight > 0 && itemHeight <= tm.tmHeight, "Unexpected item height %d, expected %d.\n",
        itemHeight, tm.tmHeight);
    itemHeight = SendMessageA(hLB, LB_GETITEMHEIGHT, -5, 0);
    ok(itemHeight > 0 && itemHeight <= tm.tmHeight, "Unexpected item height %d, expected %d.\n",
        itemHeight, tm.tmHeight);

    DestroyWindow (hLB);
}