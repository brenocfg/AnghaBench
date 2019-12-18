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
typedef  scalar_t__ LONG_PTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ERROR_INVALID_WINDOW_HANDLE ; 
 int /*<<< orphan*/ * ERROR_TLW_WITH_WSCHILD ; 
 int /*<<< orphan*/ * GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int WS_CHILD ; 
 int WS_POPUP ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Test_Params(void)
{
    HWND hWnd;
    DWORD dwError;

    SetLastError(0x1234);
    hWnd = CreateWindowExW(0, L"BUTTON", NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
    dwError = GetLastError();
    ok(hWnd != NULL, "hWnd = %p\n", hWnd);
    ok(dwError == 0, "error = %lu\n", dwError);
    DestroyWindow(hWnd);

    SetLastError(0x1234);
    hWnd = CreateWindowExW(0, L"BUTTON", NULL, 0, 0, 0, 0, 0, (HWND)(LONG_PTR)-1, NULL, NULL, NULL);
    dwError = GetLastError();
    ok(hWnd == NULL, "hWnd = %p\n", hWnd);
    ok(dwError == ERROR_INVALID_WINDOW_HANDLE, "error = %lu\n", dwError);

    SetLastError(0x1234);
    hWnd = CreateWindowExW(0, L"BUTTON", NULL, WS_CHILD, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
    dwError = GetLastError();
    ok(hWnd == NULL, "hWnd = %p\n", hWnd);
    ok(dwError == ERROR_TLW_WITH_WSCHILD, "error = %lu\n", dwError);

    SetLastError(0x1234);
    hWnd = CreateWindowExW(0, L"BUTTON", NULL, WS_CHILD, 0, 0, 0, 0, (HWND)(LONG_PTR)-1, NULL, NULL, NULL);
    dwError = GetLastError();
    ok(hWnd == NULL, "hWnd = %p\n", hWnd);
    ok(dwError == ERROR_INVALID_WINDOW_HANDLE, "error = %lu\n", dwError);

    SetLastError(0x1234);
    hWnd = CreateWindowExW(0, L"BUTTON", NULL, WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
    dwError = GetLastError();
    ok(hWnd != NULL, "hWnd = %p\n", hWnd);
    ok(dwError == 0, "error = %lu\n", dwError);
    DestroyWindow(hWnd);

    SetLastError(0x1234);
    hWnd = CreateWindowExW(0, L"BUTTON", NULL, WS_POPUP, 0, 0, 0, 0, (HWND)(LONG_PTR)-1, NULL, NULL, NULL);
    dwError = GetLastError();
    ok(hWnd == NULL, "hWnd = %p\n", hWnd);
    ok(dwError == ERROR_INVALID_WINDOW_HANDLE, "error = %lu\n", dwError);

    SetLastError(0x1234);
    hWnd = CreateWindowExW(0, L"BUTTON", NULL, WS_CHILD|WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
    dwError = GetLastError();
    ok(hWnd != NULL, "hWnd = %p\n", hWnd);
    ok(dwError == 0, "error = %lu\n", dwError);
    DestroyWindow(hWnd);

    SetLastError(0x1234);
    hWnd = CreateWindowExW(0, L"BUTTON", NULL, WS_CHILD|WS_POPUP, 0, 0, 0, 0, (HWND)(LONG_PTR)-1, NULL, NULL, NULL);
    dwError = GetLastError();
    ok(hWnd == NULL, "hWnd = %p\n", hWnd);
    ok(dwError == ERROR_INVALID_WINDOW_HANDLE, "error = %lu\n", dwError);
}