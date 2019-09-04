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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IDirectInputA ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowA (char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DIERR_OLDDIRECTINPUTVERSION ; 
 int /*<<< orphan*/  DIRECTINPUT_VERSION ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ DirectInputCreateA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_Release (int /*<<< orphan*/ *) ; 
 int SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_set_coop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mouse_tests(void)
{
    HRESULT hr;
    IDirectInputA *pDI = NULL;
    HINSTANCE hInstance = GetModuleHandleW(NULL);
    HWND hwnd;
    ULONG ref = 0;

    hr = DirectInputCreateA(hInstance, DIRECTINPUT_VERSION, &pDI, NULL);
    if (hr == DIERR_OLDDIRECTINPUTVERSION)
    {
        skip("Tests require a newer dinput version\n");
        return;
    }
    ok(SUCCEEDED(hr), "DirectInputCreateA() failed: %08x\n", hr);
    if (FAILED(hr)) return;

    hwnd = CreateWindowA("static", "Title", WS_OVERLAPPEDWINDOW, 10, 10, 200, 200, NULL, NULL,
                         NULL, NULL);
    ok(hwnd != NULL, "err: %d\n", GetLastError());
    if (hwnd)
    {
        ShowWindow(hwnd, SW_SHOW);

        test_set_coop(pDI, hwnd);
        test_acquire(pDI, hwnd);

        DestroyWindow(hwnd);
    }
    if (pDI) ref = IUnknown_Release(pDI);
    ok(!ref, "IDirectInput_Release() reference count = %d\n", ref);
}