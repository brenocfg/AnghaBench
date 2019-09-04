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
typedef  int /*<<< orphan*/  diprg ;
struct TYPE_5__ {int dwSize; int dwHeaderSize; scalar_t__ dwObj; int /*<<< orphan*/  dwHow; } ;
struct TYPE_4__ {TYPE_3__ diph; } ;
typedef  int /*<<< orphan*/  IDirectInputDeviceA ;
typedef  int /*<<< orphan*/  IDirectInputA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DIPROPRANGE ;
typedef  int /*<<< orphan*/  DIPROPHEADER ;

/* Variables and functions */
 scalar_t__ DIERR_UNSUPPORTED ; 
 int /*<<< orphan*/  DIPH_DEVICE ; 
 int /*<<< orphan*/  DIPROP_RANGE ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GUID_SysKeyboard ; 
 scalar_t__ IDirectInputDevice_GetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ IDirectInput_CreateDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int SUCCEEDED (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_get_prop(IDirectInputA *pDI, HWND hwnd)
{
    HRESULT hr;
    IDirectInputDeviceA *pKeyboard = NULL;
    DIPROPRANGE diprg;

    hr = IDirectInput_CreateDevice(pDI, &GUID_SysKeyboard, &pKeyboard, NULL);
    ok(SUCCEEDED(hr), "IDirectInput_CreateDevice() failed: %08x\n", hr);
    if (FAILED(hr)) return;

    memset(&diprg, 0, sizeof(diprg));
    diprg.diph.dwSize       = sizeof(DIPROPRANGE);
    diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    diprg.diph.dwHow        = DIPH_DEVICE;
    diprg.diph.dwObj        = 0;

    hr = IDirectInputDevice_GetProperty(pKeyboard, DIPROP_RANGE, &diprg.diph);
    ok(hr == DIERR_UNSUPPORTED, "IDirectInputDevice_GetProperty() did not return DIPROP_RANGE but: %08x\n", hr);

    if (pKeyboard) IUnknown_Release(pKeyboard);
}