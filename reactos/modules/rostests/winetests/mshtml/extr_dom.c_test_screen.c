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
struct TYPE_3__ {int bottom; int top; int right; int left; } ;
typedef  TYPE_1__ RECT ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLScreen ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 int /*<<< orphan*/  CreateICA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DIID_DispHTMLScreen ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HORZRES ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLScreen_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLScreen_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLScreen_get_availHeight (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IHTMLScreen_get_availWidth (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IHTMLScreen_get_colorDepth (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IHTMLScreen_get_height (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IHTMLScreen_get_width (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IHTMLWindow2_get_screen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  SPI_GETWORKAREA ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERTRES ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_disp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_screen(IHTMLWindow2 *window)
{
    IHTMLScreen *screen, *screen2;
    IDispatchEx *dispex;
    RECT work_area;
    LONG l, exl;
    HDC hdc;
    HRESULT hres;

    screen = NULL;
    hres = IHTMLWindow2_get_screen(window, &screen);
    ok(hres == S_OK, "get_screen failed: %08x\n", hres);
    ok(screen != NULL, "screen == NULL\n");

    screen2 = NULL;
    hres = IHTMLWindow2_get_screen(window, &screen2);
    ok(hres == S_OK, "get_screen failed: %08x\n", hres);
    ok(screen2 != NULL, "screen == NULL\n");
    ok(iface_cmp((IUnknown*)screen2, (IUnknown*)screen), "screen2 != screen\n");
    IHTMLScreen_Release(screen2);

    hres = IHTMLScreen_QueryInterface(screen, &IID_IDispatchEx, (void**)&dispex);
    ok(hres == S_OK || broken(hres == E_NOINTERFACE), "Could not get IDispatchEx interface: %08x\n", hres);
    if(SUCCEEDED(hres)) {
        test_disp((IUnknown*)screen, &DIID_DispHTMLScreen, "[object]");
        IDispatchEx_Release(dispex);
    }

    hdc = CreateICA("DISPLAY", NULL, NULL, NULL);

    exl = GetDeviceCaps(hdc, HORZRES);
    l = 0xdeadbeef;
    hres = IHTMLScreen_get_width(screen, &l);
    ok(hres == S_OK, "get_width failed: %08x\n", hres);
    ok(l == exl, "width = %d, expected %d\n", l, exl);

    exl = GetDeviceCaps(hdc, VERTRES);
    l = 0xdeadbeef;
    hres = IHTMLScreen_get_height(screen, &l);
    ok(hres == S_OK, "get_height failed: %08x\n", hres);
    ok(l == exl, "height = %d, expected %d\n", l, exl);

    exl = GetDeviceCaps(hdc, BITSPIXEL);
    l = 0xdeadbeef;
    hres = IHTMLScreen_get_colorDepth(screen, &l);
    ok(hres == S_OK, "get_height failed: %08x\n", hres);
    ok(l == exl, "height = %d, expected %d\n", l, exl);

    DeleteObject(hdc);

    SystemParametersInfoW(SPI_GETWORKAREA, 0, &work_area, 0);

    l = 0xdeadbeef;
    hres = IHTMLScreen_get_availHeight(screen, &l);
    ok(hres == S_OK, "get_availHeight failed: %08x\n", hres);
    ok(l == work_area.bottom-work_area.top, "availHeight = %d, expected %d\n", l, work_area.bottom-work_area.top);

    l = 0xdeadbeef;
    hres = IHTMLScreen_get_availWidth(screen, &l);
    ok(hres == S_OK, "get_availWidth failed: %08x\n", hres);
    ok(l == work_area.right-work_area.left, "availWidth = %d, expected %d\n", l, work_area.right-work_area.left);

    IHTMLScreen_Release(screen);
}