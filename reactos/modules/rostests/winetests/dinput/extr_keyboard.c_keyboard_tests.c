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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowA (char*,char*,int,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DIERR_OLDDIRECTINPUTVERSION ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_FRENCH ; 
 int /*<<< orphan*/  LANG_GERMAN ; 
 int /*<<< orphan*/  LANG_JAPANESE ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_FRENCH ; 
 int /*<<< orphan*/  SUBLANG_GERMAN ; 
 int /*<<< orphan*/  SUBLANG_JAPANESE_JAPAN ; 
 int SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  SetForegroundWindow (int /*<<< orphan*/ *) ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  acquire_tests (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pDirectInputCreateA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pump_messages () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_GetDeviceInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_capabilities (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_dik_codes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_get_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_set_coop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keyboard_tests(DWORD version)
{
    HRESULT hr;
    IDirectInputA *pDI = NULL;
    HINSTANCE hInstance = GetModuleHandleW(NULL);
    HWND hwnd;
    ULONG ref = 0;

    hr = pDirectInputCreateA(hInstance, version, &pDI, NULL);
    if (hr == DIERR_OLDDIRECTINPUTVERSION)
    {
        skip("Tests require a newer dinput version\n");
        return;
    }
    ok(SUCCEEDED(hr), "DirectInputCreateA() failed: %08x\n", hr);
    if (FAILED(hr)) return;

    hwnd = CreateWindowA("static", "Title", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 10, 10, 200, 200,
                         NULL, NULL, NULL, NULL);
    ok(hwnd != NULL, "err: %d\n", GetLastError());
    SetForegroundWindow( hwnd );

    if (hwnd)
    {
        pump_messages();

        acquire_tests(pDI, hwnd);
        test_set_coop(pDI, hwnd);
        test_get_prop(pDI, hwnd);
        test_capabilities(pDI, hwnd);
        test_GetDeviceInfo(pDI);

        test_dik_codes(pDI, hwnd, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT));
        test_dik_codes(pDI, hwnd, MAKELANGID(LANG_FRENCH, SUBLANG_FRENCH));
        test_dik_codes(pDI, hwnd, MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN));
        test_dik_codes(pDI, hwnd, MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN));
    }

    DestroyWindow(hwnd);
    if (pDI) ref = IUnknown_Release(pDI);
    ok(!ref, "IDirectInput_Release() reference count = %d\n", ref);
}