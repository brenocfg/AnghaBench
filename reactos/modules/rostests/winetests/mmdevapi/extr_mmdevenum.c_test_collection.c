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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ LONG_PTR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMMDeviceEnumerator ;
typedef  int /*<<< orphan*/  IMMDeviceCollection ;
typedef  int /*<<< orphan*/  IMMDevice ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int E_INVALIDARG ; 
 int E_NOINTERFACE ; 
 int E_POINTER ; 
 int /*<<< orphan*/  IID_IMMDeviceCollection ; 
 int /*<<< orphan*/  IID_IMMDeviceEnumerator ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int IMMDeviceCollection_AddRef (int /*<<< orphan*/ *) ; 
 int IMMDeviceCollection_GetCount (int /*<<< orphan*/ *,scalar_t__*) ; 
 int IMMDeviceCollection_Item (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int IMMDeviceCollection_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMMDeviceCollection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_AddRef (int /*<<< orphan*/ *) ; 
 int IMMDeviceEnumerator_GetDevice (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IMMDeviceEnumerator_Release (int /*<<< orphan*/ *) ; 
 int IMMDevice_GetId (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMMDevice_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_collection(IMMDeviceEnumerator *mme, IMMDeviceCollection *col)
{
    IMMDeviceCollection *col2;
    IMMDeviceEnumerator *mme2;
    IUnknown *unk;
    HRESULT hr;
    ULONG ref;
    UINT numdev;
    IMMDevice *dev;

    /* collection doesn't keep a ref on parent */
    IMMDeviceEnumerator_AddRef(mme);
    ref = IMMDeviceEnumerator_Release(mme);
    ok(ref == 2, "Reference count on parent is %u\n", ref);

    ref = IMMDeviceCollection_AddRef(col);
    IMMDeviceCollection_Release(col);
    ok(ref == 2, "Invalid reference count %u on collection\n", ref);

    hr = IMMDeviceCollection_QueryInterface(col, &IID_IUnknown, NULL);
    ok(hr == E_POINTER, "Null ppv returns %08x\n", hr);

    hr = IMMDeviceCollection_QueryInterface(col, &IID_IUnknown, (void**)&unk);
    ok(hr == S_OK, "Cannot query for IID_IUnknown: 0x%08x\n", hr);
    if (hr == S_OK)
    {
        ok((IUnknown*)col == unk, "Pointers are not identical %p/%p/%p\n", col, unk, mme);
        IUnknown_Release(unk);
    }

    hr = IMMDeviceCollection_QueryInterface(col, &IID_IMMDeviceCollection, (void**)&col2);
    ok(hr == S_OK, "Cannot query for IID_IMMDeviceCollection: 0x%08x\n", hr);
    if (hr == S_OK)
        IMMDeviceCollection_Release(col2);

    hr = IMMDeviceCollection_QueryInterface(col, &IID_IMMDeviceEnumerator, (void**)&mme2);
    ok(hr == E_NOINTERFACE, "Query for IID_IMMDeviceEnumerator returned: 0x%08x\n", hr);
    if (hr == S_OK)
        IMMDeviceEnumerator_Release(mme2);

    hr = IMMDeviceCollection_GetCount(col, NULL);
    ok(hr == E_POINTER, "GetCount returned 0x%08x\n", hr);

    hr = IMMDeviceCollection_GetCount(col, &numdev);
    ok(hr == S_OK, "GetCount returned 0x%08x\n", hr);

    dev = (void*)(LONG_PTR)0x12345678;
    hr = IMMDeviceCollection_Item(col, numdev, &dev);
    ok(hr == E_INVALIDARG, "Asking for too high device returned 0x%08x\n", hr);
    ok(dev == NULL, "Returned non-null device\n");

    if (numdev)
    {
        hr = IMMDeviceCollection_Item(col, 0, NULL);
        ok(hr == E_POINTER, "Query with null pointer returned 0x%08x\n", hr);

        hr = IMMDeviceCollection_Item(col, 0, &dev);
        ok(hr == S_OK, "Valid Item returned 0x%08x\n", hr);
        ok(dev != NULL, "Device is null!\n");
        if (dev != NULL)
        {
            char temp[128];
            WCHAR *id = NULL;
            if (IMMDevice_GetId(dev, &id) == S_OK)
            {
                IMMDevice *dev2;

                temp[sizeof(temp)-1] = 0;
                WideCharToMultiByte(CP_ACP, 0, id, -1, temp, sizeof(temp)-1, NULL, NULL);
                trace("Device found: %s\n", temp);

                hr = IMMDeviceEnumerator_GetDevice(mme, id, &dev2);
                ok(hr == S_OK, "GetDevice failed: %08x\n", hr);

                IMMDevice_Release(dev2);

                CoTaskMemFree(id);
            }
        }
        if (dev)
            IMMDevice_Release(dev);
    }
    IMMDeviceCollection_Release(col);
}