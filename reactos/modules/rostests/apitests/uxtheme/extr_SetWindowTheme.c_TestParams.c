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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_HANDLE ; 
 scalar_t__ S_OK ; 
 scalar_t__ SetWindowTheme (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

void TestParams(HWND hwnd)
{
    HRESULT hr;

    hr = SetWindowTheme(0, NULL, NULL);
    ok (hr == E_HANDLE, "Expected E_HANDLE got 0x%lx error\n", hr);

    hr = SetWindowTheme((HWND)(ULONG_PTR)0xdeaddeaddeaddeadULL, NULL, NULL);
    ok (hr == E_HANDLE, "Expected E_HANDLE got 0x%lx error\n", hr);

    hr = SetWindowTheme(hwnd, NULL, NULL);
    ok (hr == S_OK, "Expected S_OK got 0x%lx error\n", hr);

    hr = SetWindowTheme(hwnd, L"none", L"none");
    ok (hr == S_OK, "Expected S_OK got 0x%lx error\n", hr);

    hr = SetWindowTheme(hwnd, NULL, L"none");
    ok (hr == S_OK, "Expected S_OK got 0x%lx error\n", hr);

    hr = SetWindowTheme(hwnd, L"none", NULL);
    ok (hr == S_OK, "Expected S_OK got 0x%lx error\n", hr);

    hr = SetWindowTheme(hwnd, L"", L"");
    ok (hr == S_OK, "Expected S_OK got 0x%lx error\n", hr);
}