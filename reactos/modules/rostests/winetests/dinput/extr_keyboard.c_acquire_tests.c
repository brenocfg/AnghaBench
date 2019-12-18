#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kbd_state ;
typedef  int /*<<< orphan*/  df ;
typedef  int /*<<< orphan*/  custom_state ;
typedef  int UINT ;
struct TYPE_4__ {int dwSize; int dwObjSize; int dwDataSize; int dwNumObjs; scalar_t__* rgodf; int /*<<< orphan*/  dwFlags; } ;
typedef  int /*<<< orphan*/  RAWINPUTDEVICE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IDirectInputDeviceA ;
typedef  int /*<<< orphan*/  IDirectInputA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  HKL ;
typedef  scalar_t__ DIOBJECTDATAFORMAT ;
typedef  TYPE_1__ DIDATAFORMAT ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  ActivateKeyboardLayout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DIDFT_BUTTON ; 
 int DIDFT_MAKEINSTANCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIDF_RELAXIS ; 
 int DIERR_INVALIDPARAM ; 
 int DIERR_NOTACQUIRED ; 
 int /*<<< orphan*/  DIK_E ; 
 int /*<<< orphan*/  DIK_Q ; 
 int /*<<< orphan*/  DIK_R ; 
 int /*<<< orphan*/  DIK_W ; 
 int DISCL_BACKGROUND ; 
 int DISCL_NONEXCLUSIVE ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  GUID_Key ; 
 int /*<<< orphan*/  GUID_SysKeyboard ; 
 int /*<<< orphan*/  GetRegisteredRawInputDevices (int /*<<< orphan*/ *,int*,int) ; 
 int IDirectInputDevice_Acquire (int /*<<< orphan*/ *) ; 
 int IDirectInputDevice_GetDeviceState (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int IDirectInputDevice_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int IDirectInputDevice_SetDataFormat (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int IDirectInputDevice_Unacquire (int /*<<< orphan*/ *) ; 
 int IDirectInput_CreateDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEYEVENTF_KEYUP ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int SUCCEEDED (int) ; 
 int S_FALSE ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnloadKeyboardLayout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activate_keyboard_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 TYPE_1__ c_dfDIKeyboard ; 
 int /*<<< orphan*/  keybd_event (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  pump_messages () ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void acquire_tests(IDirectInputA *pDI, HWND hwnd)
{
    HRESULT hr;
    IDirectInputDeviceA *pKeyboard;
    BYTE kbd_state[256];
    LONG custom_state[6];
    int i;
    DIOBJECTDATAFORMAT dodf[] =
        {
            { &GUID_Key, sizeof(LONG) * 0, DIDFT_MAKEINSTANCE(DIK_Q)|DIDFT_BUTTON, 0 },
            { &GUID_Key, sizeof(LONG) * 1, DIDFT_MAKEINSTANCE(DIK_W)|DIDFT_BUTTON, 0 },
            { &GUID_Key, sizeof(LONG) * 2, DIDFT_MAKEINSTANCE(DIK_E)|DIDFT_BUTTON, 0 },
            { &GUID_Key, sizeof(LONG) * 4, DIDFT_MAKEINSTANCE(DIK_R)|DIDFT_BUTTON, 0 },
        };
    DIDATAFORMAT df;
    HKL hkl, hkl_orig;
    UINT prev_raw_devices_count, raw_devices_count;

    hkl = activate_keyboard_layout(MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), &hkl_orig);
    if (!hkl) return;

    df.dwSize = sizeof( df );
    df.dwObjSize = sizeof( DIOBJECTDATAFORMAT );
    df.dwFlags = DIDF_RELAXIS;
    df.dwDataSize = sizeof( custom_state );
    df.dwNumObjs = ARRAY_SIZE(dodf);
    df.rgodf = dodf;

    hr = IDirectInput_CreateDevice(pDI, &GUID_SysKeyboard, &pKeyboard, NULL);
    ok(SUCCEEDED(hr), "IDirectInput_CreateDevice() failed: %08x\n", hr);
    if (FAILED(hr)) return;

    hr = IDirectInputDevice_SetDataFormat(pKeyboard, &c_dfDIKeyboard);
    ok(SUCCEEDED(hr), "IDirectInputDevice_SetDataFormat() failed: %08x\n", hr);
    hr = IDirectInputDevice_SetCooperativeLevel(pKeyboard, NULL, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
    ok(SUCCEEDED(hr), "IDirectInputDevice_SetCooperativeLevel() failed: %08x\n", hr);
    hr = IDirectInputDevice_GetDeviceState(pKeyboard, 10, kbd_state);
    ok(hr == DIERR_NOTACQUIRED, "IDirectInputDevice_GetDeviceState(10,) should have failed: %08x\n", hr);
    hr = IDirectInputDevice_GetDeviceState(pKeyboard, sizeof(kbd_state), kbd_state);
    ok(hr == DIERR_NOTACQUIRED, "IDirectInputDevice_GetDeviceState() should have failed: %08x\n", hr);
    hr = IDirectInputDevice_Unacquire(pKeyboard);
    ok(hr == S_FALSE, "IDirectInputDevice_Unacquire() should have failed: %08x\n", hr);
    hr = IDirectInputDevice_Acquire(pKeyboard);
    ok(SUCCEEDED(hr), "IDirectInputDevice_Acquire() failed: %08x\n", hr);
    hr = IDirectInputDevice_Acquire(pKeyboard);
    ok(hr == S_FALSE, "IDirectInputDevice_Acquire() should have failed: %08x\n", hr);
    hr = IDirectInputDevice_GetDeviceState(pKeyboard, 10, kbd_state);
    ok(hr == DIERR_INVALIDPARAM, "IDirectInputDevice_GetDeviceState(10,) should have failed: %08x\n", hr);
    hr = IDirectInputDevice_GetDeviceState(pKeyboard, sizeof(kbd_state), kbd_state);
    ok(SUCCEEDED(hr), "IDirectInputDevice_GetDeviceState() failed: %08x\n", hr);
    hr = IDirectInputDevice_Unacquire(pKeyboard);
    ok(SUCCEEDED(hr), "IDirectInputDevice_Uncquire() failed: %08x\n", hr);
    hr = IDirectInputDevice_SetDataFormat( pKeyboard , &df );
    ok(SUCCEEDED(hr), "IDirectInputDevice_SetDataFormat() failed: %08x\n", hr);
    hr = IDirectInputDevice_Acquire(pKeyboard);
    ok(SUCCEEDED(hr), "IDirectInputDevice_Acquire() failed: %08x\n", hr);
    hr = IDirectInputDevice_GetDeviceState(pKeyboard, sizeof(custom_state), custom_state);
    ok(SUCCEEDED(hr), "IDirectInputDevice_GetDeviceState(4,) failed: %08x\n", hr);
    hr = IDirectInputDevice_GetDeviceState(pKeyboard, sizeof(kbd_state), kbd_state);
    ok(hr == DIERR_INVALIDPARAM, "IDirectInputDevice_GetDeviceState(256,) should have failed: %08x\n", hr);

    memset(custom_state, 0x56, sizeof(custom_state));
    IDirectInputDevice_GetDeviceState(pKeyboard, sizeof(custom_state), custom_state);
    for (i = 0; i < ARRAY_SIZE(custom_state); i++)
        ok(custom_state[i] == 0, "Should be zeroed, got 0x%08x\n", custom_state[i]);

    /* simulate some keyboard input */
    SetFocus(hwnd);
    pump_messages();

    keybd_event('Q', 0, 0, 0);
    hr = IDirectInputDevice_GetDeviceState(pKeyboard, sizeof(custom_state), custom_state);
    ok(SUCCEEDED(hr), "IDirectInputDevice_GetDeviceState() failed: %08x\n", hr);
    if (!custom_state[0])
        win_skip("Keyboard event not processed, skipping test\n");
    else
    {
        /* unacquiring should reset the device state */
        hr = IDirectInputDevice_Unacquire(pKeyboard);
        ok(SUCCEEDED(hr), "IDirectInputDevice_Unacquire() failed: %08x\n", hr);
        hr = IDirectInputDevice_Acquire(pKeyboard);
        ok(SUCCEEDED(hr), "IDirectInputDevice_Acquire() failed: %08x\n", hr);
        hr = IDirectInputDevice_GetDeviceState(pKeyboard, sizeof(custom_state), custom_state);
        ok(SUCCEEDED(hr), "IDirectInputDevice_GetDeviceState failed: %08x\n", hr);
        for (i = 0; i < ARRAY_SIZE(custom_state); i++)
            ok(custom_state[i] == 0, "Should be zeroed, got 0x%08x\n", custom_state[i]);
    }
    keybd_event('Q', 0, KEYEVENTF_KEYUP, 0);

    prev_raw_devices_count = 0;
    GetRegisteredRawInputDevices(NULL, &prev_raw_devices_count, sizeof(RAWINPUTDEVICE));
    ok(prev_raw_devices_count == 0 || broken(prev_raw_devices_count == 1) /* wxppro, w2003std */,
       "Unexpected raw devices registered: %d\n", prev_raw_devices_count);

    hr = IDirectInputDevice_Acquire(pKeyboard);
    ok(SUCCEEDED(hr), "IDirectInputDevice_Acquire() failed: %08x\n", hr);

    raw_devices_count = 0;
    GetRegisteredRawInputDevices(NULL, &raw_devices_count, sizeof(RAWINPUTDEVICE));
    ok(raw_devices_count == prev_raw_devices_count,
       "Unexpected raw devices registered: %d\n", raw_devices_count);

    hr = IDirectInputDevice_Unacquire(pKeyboard);
    ok(SUCCEEDED(hr), "IDirectInputDevice_Unacquire() failed: %08x\n", hr);

    if (pKeyboard) IUnknown_Release(pKeyboard);

    ActivateKeyboardLayout(hkl_orig, 0);
    UnloadKeyboardLayout(hkl);
}