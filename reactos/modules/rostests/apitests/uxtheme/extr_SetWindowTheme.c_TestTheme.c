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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HTHEME ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/ * OpenThemeData (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ SetWindowTheme (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void TestTheme(HWND hwnd)
{
    HRESULT hr;
    HTHEME htheme1, htheme2;

    hr = SetWindowTheme(hwnd, NULL, NULL);
    ok (hr == S_OK, "Expected S_OK got 0x%lx error\n", hr);

    htheme1 = OpenThemeData(hwnd, L"Toolbar");
    ok (htheme1 != NULL, "OpenThemeData failed\n");

    hr = SetWindowTheme(hwnd, L"", L"");
    ok (hr == S_OK, "Expected S_OK got 0x%lx error\n", hr);

    htheme2 = OpenThemeData(hwnd, L"Toolbar");
    ok (htheme2 == NULL, "Expected OpenThemeData to fail\n");

    hr = SetWindowTheme(hwnd, L"TrayNotify", L"");
    ok (hr == S_OK, "Expected S_OK got 0x%lx error\n", hr);

    htheme2 = OpenThemeData(hwnd, L"Toolbar");
    ok (htheme2 == NULL, "Expected OpenThemeData to fail\n");

    hr = SetWindowTheme(hwnd, L"TrayNotify", NULL);
    ok (hr == S_OK, "Expected S_OK got 0x%lx error\n", hr);

    htheme2 = OpenThemeData(hwnd, L"Toolbar");
    ok (htheme2 != NULL, "OpenThemeData failed\n");

    ok(htheme1 != htheme2, "Expected different theme data\n");
}