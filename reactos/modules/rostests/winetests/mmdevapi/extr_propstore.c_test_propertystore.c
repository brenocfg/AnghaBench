#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  temp ;
struct TYPE_5__ {scalar_t__ pwszVal; } ;
struct TYPE_6__ {scalar_t__ vt; TYPE_1__ u; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  int /*<<< orphan*/  PROPERTYKEY ;
typedef  int /*<<< orphan*/  IPropertyStore ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DEVPKEY_DeviceInterface_ClassGuid ; 
 int /*<<< orphan*/  DEVPKEY_DeviceInterface_Enabled ; 
 int /*<<< orphan*/  DEVPKEY_DeviceInterface_FriendlyName ; 
 scalar_t__ IPropertyStore_GetValue (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/  const PKEY_AudioEndpoint_GUID ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ VT_EMPTY ; 
 scalar_t__ VT_LPWSTR ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_propertystore(IPropertyStore *store)
{
    HRESULT hr;
    PROPVARIANT pv;
    char temp[128];
    temp[sizeof(temp)-1] = 0;

    pv.vt = VT_EMPTY;
    hr = IPropertyStore_GetValue(store, &PKEY_AudioEndpoint_GUID, &pv);
    ok(hr == S_OK, "Failed with %08x\n", hr);
    ok(pv.vt == VT_LPWSTR, "Value should be %i, is %i\n", VT_LPWSTR, pv.vt);
    if (hr == S_OK && pv.vt == VT_LPWSTR)
    {
        WideCharToMultiByte(CP_ACP, 0, pv.u.pwszVal, -1, temp, sizeof(temp)-1, NULL, NULL);
        trace("guid: %s\n", temp);
        PropVariantClear(&pv);
    }

    pv.vt = VT_EMPTY;
    hr = IPropertyStore_GetValue(store, (const PROPERTYKEY*)&DEVPKEY_DeviceInterface_FriendlyName, &pv);
    ok(hr == S_OK, "Failed with %08x\n", hr);
    ok(pv.vt == VT_LPWSTR && pv.u.pwszVal, "FriendlyName value had wrong type: 0x%x or was NULL\n", pv.vt);
    PropVariantClear(&pv);

    pv.vt = VT_EMPTY;
    hr = IPropertyStore_GetValue(store, (const PROPERTYKEY*)&DEVPKEY_DeviceInterface_Enabled, &pv);
    ok(hr == S_OK, "Failed with %08x\n", hr);
    ok(pv.vt == VT_EMPTY, "Key should not be found\n");
    PropVariantClear(&pv);

    pv.vt = VT_EMPTY;
    hr = IPropertyStore_GetValue(store, (const PROPERTYKEY*)&DEVPKEY_DeviceInterface_ClassGuid, &pv);
    ok(hr == S_OK, "Failed with %08x\n", hr);
    ok(pv.vt == VT_EMPTY, "Key should not be found\n");
    PropVariantClear(&pv);
}