#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scheme ;
struct TYPE_4__ {int dwSize; int clrBtnHighlight; int clrBtnShadow; } ;
struct TYPE_3__ {int clrFore; int clrBack; int /*<<< orphan*/  fMask; int /*<<< orphan*/  cbSize; } ;
typedef  TYPE_1__ REBARBANDINFOA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ COLORSCHEME ;
typedef  int COLORREF ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_DEFAULT ; 
 int /*<<< orphan*/  CLR_NONE ; 
 int /*<<< orphan*/  COLOR_3DFACE ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBBIM_COLORS ; 
 int /*<<< orphan*/  RB_GETBANDINFOA ; 
 int /*<<< orphan*/  RB_GETBKCOLOR ; 
 int /*<<< orphan*/  RB_GETCOLORSCHEME ; 
 int /*<<< orphan*/  RB_GETTEXTCOLOR ; 
 int /*<<< orphan*/  RB_SETTEXTCOLOR ; 
 int /*<<< orphan*/  REBARBANDINFOA_V6_SIZE ; 
 int /*<<< orphan*/  RGB (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_band_w (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  compare (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_rebar_control () ; 
 int /*<<< orphan*/  ok (void*,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_colors(void)
{
    COLORSCHEME scheme;
    COLORREF clr;
    BOOL ret;
    HWND hRebar;
    REBARBANDINFOA bi;

    hRebar = create_rebar_control();

    /* test default colors */
    clr = SendMessageA(hRebar, RB_GETTEXTCOLOR, 0, 0);
    compare(clr, CLR_NONE, "%x");
    clr = SendMessageA(hRebar, RB_GETBKCOLOR, 0, 0);
    compare(clr, CLR_NONE, "%x");

    scheme.dwSize = sizeof(scheme);
    scheme.clrBtnHighlight = 0;
    scheme.clrBtnShadow = 0;
    ret = SendMessageA(hRebar, RB_GETCOLORSCHEME, 0, (LPARAM)&scheme);
    if (ret)
    {
        compare(scheme.clrBtnHighlight, CLR_DEFAULT, "%x");
        compare(scheme.clrBtnShadow, CLR_DEFAULT, "%x");
    }
    else
        skip("RB_GETCOLORSCHEME not supported\n");

    /* check default band colors */
    add_band_w(hRebar, "", 0, 10, 10);
    bi.cbSize = REBARBANDINFOA_V6_SIZE;
    bi.fMask = RBBIM_COLORS;
    bi.clrFore = bi.clrBack = 0xc0ffe;
    ret = SendMessageA(hRebar, RB_GETBANDINFOA, 0, (LPARAM)&bi);
    ok(ret, "RB_GETBANDINFOA failed\n");
    compare(bi.clrFore, RGB(0, 0, 0), "%x");
    compare(bi.clrBack, GetSysColor(COLOR_3DFACE), "%x");

    SendMessageA(hRebar, RB_SETTEXTCOLOR, 0, RGB(255, 0, 0));
    bi.clrFore = bi.clrBack = 0xc0ffe;
    ret = SendMessageA(hRebar, RB_GETBANDINFOA, 0, (LPARAM)&bi);
    ok(ret, "RB_GETBANDINFOA failed\n");
    compare(bi.clrFore, RGB(0, 0, 0), "%x");

    DestroyWindow(hRebar);
}