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
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DKGRAY_BRUSH ; 
 int /*<<< orphan*/  DST_TEXT ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int DrawStateA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WS_POPUP ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void test_DrawState(void)
{
    static const char text[] = "Sample text string";
    HWND hwnd;
    HDC hdc;
    BOOL ret;

    hwnd = CreateWindowExA(0, "static", NULL, WS_POPUP,
                           0, 0, 200, 200, 0, 0, 0, NULL);
    assert(hwnd);

    hdc = GetDC(hwnd);
    assert(hdc);

    SetLastError(0xdeadbeef);
    ret = DrawStateA(hdc, GetStockObject(DKGRAY_BRUSH), NULL, (LPARAM)text, strlen(text),
                    0, 0, 10, 10, DST_TEXT);
    ok(ret, "DrawState error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = DrawStateA(hdc, GetStockObject(DKGRAY_BRUSH), NULL, (LPARAM)text, 0,
                    0, 0, 10, 10, DST_TEXT);
    ok(ret, "DrawState error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = DrawStateA(hdc, GetStockObject(DKGRAY_BRUSH), NULL, 0, strlen(text),
                    0, 0, 10, 10, DST_TEXT);
    ok(!ret || broken(ret) /* win98 */, "DrawState succeeded\n");
    ok(GetLastError() == 0xdeadbeef, "not expected error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = DrawStateA(hdc, GetStockObject(DKGRAY_BRUSH), NULL, 0, 0,
                    0, 0, 10, 10, DST_TEXT);
    ok(!ret || broken(ret) /* win98 */, "DrawState succeeded\n");
    ok(GetLastError() == 0xdeadbeef, "not expected error %u\n", GetLastError());

    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}