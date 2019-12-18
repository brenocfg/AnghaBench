#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mouse_state ;
typedef  int /*<<< orphan*/  m_state ;
typedef  int /*<<< orphan*/  di_op ;
struct TYPE_5__ {int dwSize; int dwHeaderSize; int dwObj; int /*<<< orphan*/  dwHow; } ;
struct TYPE_4__ {int dwData; TYPE_3__ diph; } ;
typedef  int /*<<< orphan*/  LPCDIPROPHEADER ;
typedef  int /*<<< orphan*/  IDirectInputDeviceA ;
typedef  int /*<<< orphan*/  IDirectInputA ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DIPROPHEADER ;
typedef  TYPE_1__ DIPROPDWORD ;
typedef  int /*<<< orphan*/  DIMOUSESTATE ;
typedef  int /*<<< orphan*/  DIDEVICEOBJECTDATA ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowA (char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DIDFT_MAKEINSTANCE (int) ; 
 int DIDFT_RELAXIS ; 
 scalar_t__ DIERR_NOTACQUIRED ; 
 scalar_t__ DIERR_OTHERAPPHASPRIO ; 
 int DIMOFS_Y ; 
 int /*<<< orphan*/  DIPH_BYID ; 
 int /*<<< orphan*/  DIPH_BYOFFSET ; 
 int /*<<< orphan*/  DIPH_DEVICE ; 
 int /*<<< orphan*/  DIPROP_BUFFERSIZE ; 
 int /*<<< orphan*/  DIPROP_GRANULARITY ; 
 int DISCL_FOREGROUND ; 
 int DISCL_NONEXCLUSIVE ; 
 scalar_t__ DI_OK ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GUID_SysMouse ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ IDirectInputDevice_Acquire (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectInputDevice_GetDeviceData (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectInputDevice_GetDeviceState (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectInputDevice_GetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ IDirectInputDevice_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ IDirectInputDevice_SetDataFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectInputDevice_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectInputDevice_Unacquire (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectInput_CreateDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MOUSEEVENTF_MOVE ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetActiveWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetForegroundWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WS_VISIBLE ; 
 int /*<<< orphan*/  c_dfDIMouse ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mouse_event (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  winetest_interactive ; 

__attribute__((used)) static void test_acquire(IDirectInputA *pDI, HWND hwnd)
{
    HRESULT hr;
    IDirectInputDeviceA *pMouse = NULL;
    DIMOUSESTATE m_state;
    HWND hwnd2;
    DIPROPDWORD di_op;
    DIDEVICEOBJECTDATA mouse_state;
    DWORD cnt;
    int i;

    if (! SetForegroundWindow(hwnd))
    {
        skip("Not running as foreground app, skipping acquire tests\n");
        return;
    }

    hr = IDirectInput_CreateDevice(pDI, &GUID_SysMouse, &pMouse, NULL);
    ok(SUCCEEDED(hr), "IDirectInput_CreateDevice() failed: %08x\n", hr);
    if (FAILED(hr)) return;

    hr = IDirectInputDevice_SetCooperativeLevel(pMouse, hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    ok(hr == S_OK, "SetCooperativeLevel: %08x\n", hr);

    memset(&di_op, 0, sizeof(di_op));
    di_op.dwData = 5;
    di_op.diph.dwHow = DIPH_DEVICE;
    di_op.diph.dwSize = sizeof(DIPROPDWORD);
    di_op.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    hr = IDirectInputDevice_SetProperty(pMouse, DIPROP_BUFFERSIZE, (LPCDIPROPHEADER)&di_op);
    ok(hr == S_OK, "SetProperty() failed: %08x\n", hr);

    hr = IDirectInputDevice_SetDataFormat(pMouse, &c_dfDIMouse);
    ok(SUCCEEDED(hr), "IDirectInputDevice_SetDataFormat() failed: %08x\n", hr);
    hr = IDirectInputDevice_Unacquire(pMouse);
    ok(hr == S_FALSE, "IDirectInputDevice_Unacquire() should have failed: %08x\n", hr);
    hr = IDirectInputDevice_Acquire(pMouse);
    ok(SUCCEEDED(hr), "IDirectInputDevice_Acquire() failed: %08x\n", hr);
    hr = IDirectInputDevice_Acquire(pMouse);
    ok(hr == S_FALSE, "IDirectInputDevice_Acquire() should have failed: %08x\n", hr);

    /* Foreground coop level requires window to have focus */
    /* Create a temporary window, this should make dinput
     * lose mouse input */
    hwnd2 = CreateWindowA("static", "Temporary", WS_VISIBLE, 10, 210, 200, 200, NULL, NULL, NULL,
                          NULL);
    ok(hwnd2 != NULL, "CreateWindowA failed with %u\n", GetLastError());

    hr = IDirectInputDevice_GetDeviceState(pMouse, sizeof(m_state), &m_state);
    ok(hr == DIERR_NOTACQUIRED, "GetDeviceState() should have failed: %08x\n", hr);

    hr = IDirectInputDevice_Acquire(pMouse);
    ok(hr == DIERR_OTHERAPPHASPRIO, "Acquire() should have failed: %08x\n", hr);

    SetActiveWindow( hwnd );
    hr = IDirectInputDevice_Acquire(pMouse);
    ok(hr == S_OK, "Acquire() failed: %08x\n", hr);

if (!winetest_interactive)
    skip("ROSTESTS-176/CORE-9710: Skipping randomly failing tests\n");
else {

    mouse_event(MOUSEEVENTF_MOVE, 10, 10, 0, 0);
    cnt = 1;
    hr = IDirectInputDevice_GetDeviceData(pMouse, sizeof(mouse_state), &mouse_state, &cnt, 0);
    ok(hr == S_OK && cnt > 0, "GetDeviceData() failed: %08x cnt:%d\n", hr, cnt);

    mouse_event(MOUSEEVENTF_MOVE, 10, 10, 0, 0);
    hr = IDirectInputDevice_Unacquire(pMouse);
    ok(hr == S_OK, "Failed: %08x\n", hr);
    cnt = 1;
    hr = IDirectInputDevice_GetDeviceData(pMouse, sizeof(mouse_state), &mouse_state, &cnt, 0);
    ok(hr == S_OK && cnt > 0, "GetDeviceData() failed: %08x cnt:%d\n", hr, cnt);

    hr = IDirectInputDevice_Acquire(pMouse);
    ok(hr == S_OK, "Failed: %08x\n", hr);
    mouse_event(MOUSEEVENTF_MOVE, 10, 10, 0, 0);
    hr = IDirectInputDevice_Unacquire(pMouse);
    ok(hr == S_OK, "Failed: %08x\n", hr);

    hr = IDirectInputDevice_Acquire(pMouse);
    ok(hr == S_OK, "Failed: %08x\n", hr);
    cnt = 1;
    hr = IDirectInputDevice_GetDeviceData(pMouse, sizeof(mouse_state), &mouse_state, &cnt, 0);
    ok(hr == S_OK && cnt > 0, "GetDeviceData() failed: %08x cnt:%d\n", hr, cnt);

    /* Check for buffer overflow */
    for (i = 0; i < 6; i++)
        mouse_event(MOUSEEVENTF_MOVE, 10 + i, 10 + i, 0, 0);

    cnt = 1;
    hr = IDirectInputDevice_GetDeviceData(pMouse, sizeof(mouse_state), &mouse_state, &cnt, 0);
    ok(hr == DI_OK, "GetDeviceData() failed: %08x cnt:%d\n", hr, cnt);
    cnt = 1;
    hr = IDirectInputDevice_GetDeviceData(pMouse, sizeof(mouse_state), &mouse_state, &cnt, 0);
    ok(hr == DI_OK && cnt == 1, "GetDeviceData() failed: %08x cnt:%d\n", hr, cnt);

    /* Check for granularity property using BYOFFSET */
    memset(&di_op, 0, sizeof(di_op));
    di_op.diph.dwHow = DIPH_BYOFFSET;
    di_op.diph.dwObj = DIMOFS_Y;
    di_op.diph.dwSize = sizeof(DIPROPDWORD);
    di_op.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    hr = IDirectInputDevice_GetProperty(pMouse, DIPROP_GRANULARITY, &di_op.diph);
    /* Granularity of Y axis should be 1! */
    ok(hr == S_OK && di_op.dwData == 1, "GetProperty(): %08x, dwData: %i but should be 1.\n", hr, di_op.dwData);

    /* Check for granularity property using BYID */
    memset(&di_op, 0, sizeof(di_op));
    di_op.diph.dwHow = DIPH_BYID;
    /* WINE_MOUSE_Y_AXIS_INSTANCE := 1 */
    di_op.diph.dwObj = (DIDFT_MAKEINSTANCE(1) | DIDFT_RELAXIS);
    di_op.diph.dwSize = sizeof(DIPROPDWORD);
    di_op.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    hr = IDirectInputDevice_GetProperty(pMouse, DIPROP_GRANULARITY, &di_op.diph);
    /* Granularity of Y axis should be 1! */
    ok(hr == S_OK && di_op.dwData == 1, "GetProperty(): %08x, dwData: %i but should be 1.\n", hr, di_op.dwData);
}
    if (pMouse) IUnknown_Release(pMouse);

    DestroyWindow( hwnd2 );
}