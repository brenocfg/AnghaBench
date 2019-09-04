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
typedef  int /*<<< orphan*/  IDirectInputDeviceA ;
typedef  int /*<<< orphan*/  IDirectInputA ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowA (char*,char*,int,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GUID_SysKeyboard ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ IDirectInputDevice_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ IDirectInput_CreateDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 scalar_t__* SetCoop_child_window ; 
 scalar_t__* SetCoop_invalid_window ; 
 scalar_t__* SetCoop_null_window ; 
 scalar_t__* SetCoop_real_window ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_set_coop(IDirectInputA *pDI, HWND hwnd)
{
    HRESULT hr;
    IDirectInputDeviceA *pKeyboard = NULL;
    int i;
    HWND child;

    hr = IDirectInput_CreateDevice(pDI, &GUID_SysKeyboard, &pKeyboard, NULL);
    ok(SUCCEEDED(hr), "IDirectInput_CreateDevice() failed: %08x\n", hr);
    if (FAILED(hr)) return;

    for (i=0; i<16; i++)
    {
        hr = IDirectInputDevice_SetCooperativeLevel(pKeyboard, NULL, i);
        ok(hr == SetCoop_null_window[i], "SetCooperativeLevel(NULL, %d): %08x\n", i, hr);
    }
    for (i=0; i<16; i++)
    {
        hr = IDirectInputDevice_SetCooperativeLevel(pKeyboard, (HWND)0x400000, i);
        ok(hr == SetCoop_invalid_window[i], "SetCooperativeLevel(invalid, %d): %08x\n", i, hr);
    }
    for (i=0; i<16; i++)
    {
        hr = IDirectInputDevice_SetCooperativeLevel(pKeyboard, hwnd, i);
        ok(hr == SetCoop_real_window[i], "SetCooperativeLevel(hwnd, %d): %08x\n", i, hr);
    }

    child = CreateWindowA("static", "Title", WS_CHILD | WS_VISIBLE, 10, 10, 50, 50, hwnd, NULL,
                          NULL, NULL);
    ok(child != NULL, "err: %d\n", GetLastError());

    for (i=0; i<16; i++)
    {
        hr = IDirectInputDevice_SetCooperativeLevel(pKeyboard, child, i);
        ok(hr == SetCoop_child_window[i], "SetCooperativeLevel(child, %d): %08x\n", i, hr);
    }

    DestroyWindow(child);
    if (pKeyboard) IUnknown_Release(pKeyboard);
}