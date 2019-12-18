#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  instA ;
typedef  int /*<<< orphan*/  inst3A ;
struct TYPE_5__ {int dwSize; int dwDevType; int /*<<< orphan*/  guidProduct; int /*<<< orphan*/  guidInstance; } ;
struct TYPE_4__ {int dwSize; int dwDevType; int /*<<< orphan*/  guidProduct; int /*<<< orphan*/  guidInstance; } ;
typedef  int /*<<< orphan*/  IDirectInputDeviceA ;
typedef  int /*<<< orphan*/  IDirectInputA ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DIDEVICEINSTANCE_DX3A ;
typedef  TYPE_2__ DIDEVICEINSTANCEA ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUID_SysKeyboard ; 
 int /*<<< orphan*/  IDirectInputDevice_GetDeviceInfo (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  IDirectInput_CreateDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GetDeviceInfo(IDirectInputA *pDI)
{
    HRESULT hr;
    IDirectInputDeviceA *pKey = NULL;
    DIDEVICEINSTANCEA instA;
    DIDEVICEINSTANCE_DX3A inst3A;

    hr = IDirectInput_CreateDevice(pDI, &GUID_SysKeyboard, &pKey, NULL);
    ok(SUCCEEDED(hr), "IDirectInput_CreateDevice() failed: %08x\n", hr);
    if (FAILED(hr)) return;

    instA.dwSize = sizeof(instA);
    hr = IDirectInputDevice_GetDeviceInfo(pKey, &instA);
    ok(SUCCEEDED(hr), "got %08x\n", hr);

    inst3A.dwSize = sizeof(inst3A);
    hr = IDirectInputDevice_GetDeviceInfo(pKey, (DIDEVICEINSTANCEA *)&inst3A);
    ok(SUCCEEDED(hr), "got %08x\n", hr);

    ok(instA.dwSize != inst3A.dwSize, "got %d, %d \n", instA.dwSize, inst3A.dwSize);
    ok(IsEqualGUID(&instA.guidInstance, &inst3A.guidInstance), "got %s, %s\n",
            wine_dbgstr_guid(&instA.guidInstance), wine_dbgstr_guid(&inst3A.guidInstance) );
    ok(IsEqualGUID(&instA.guidProduct, &inst3A.guidProduct), "got %s, %s\n",
            wine_dbgstr_guid(&instA.guidProduct), wine_dbgstr_guid(&inst3A.guidProduct) );
    ok(instA.dwDevType == inst3A.dwDevType, "got %d, %d\n", instA.dwDevType, inst3A.dwDevType);

    IUnknown_Release(pKey);
}