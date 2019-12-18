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
typedef  int /*<<< orphan*/  temp ;
typedef  int /*<<< orphan*/  PROPERTYKEY ;
typedef  int /*<<< orphan*/  IPropertyStore ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEVPKEY_Device_DeviceDesc ; 
 int /*<<< orphan*/  DEVPKEY_Device_FriendlyName ; 
 int FALSE ; 
 scalar_t__ IPropertyStore_GetAt (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ IPropertyStore_GetCount (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IsEqualPropertyKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_getat(IPropertyStore *store)
{
    HRESULT hr;
    DWORD propcount;
    DWORD prop;
    PROPERTYKEY pkey;
    BOOL found_name = FALSE;
    BOOL found_desc = FALSE;
    char temp[128];
    temp[sizeof(temp)-1] = 0;

    hr = IPropertyStore_GetCount(store, &propcount);

    ok(hr == S_OK, "Failed with %08x\n", hr);
    ok(propcount > 0, "Propcount %d should be greater than zero\n", propcount);

    for (prop = 0; prop < propcount; prop++) {
	hr = IPropertyStore_GetAt(store, prop, &pkey);
	ok(hr == S_OK, "Failed with %08x\n", hr);
	if (IsEqualPropertyKey(pkey, DEVPKEY_Device_FriendlyName))
	    found_name = TRUE;
	if (IsEqualPropertyKey(pkey, DEVPKEY_Device_DeviceDesc))
	    found_desc = TRUE;
    }
    ok(found_name ||
            broken(!found_name) /* vista */, "DEVPKEY_Device_FriendlyName not found\n");
    ok(found_desc, "DEVPKEY_Device_DeviceDesc not found\n");
}