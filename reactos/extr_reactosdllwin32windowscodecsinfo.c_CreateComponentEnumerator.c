#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct category {int type; int /*<<< orphan*/  catid; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_14__ {TYPE_1__* DebugInfo; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int ref; TYPE_2__ IEnumUnknown_iface; int /*<<< orphan*/  objects; TYPE_5__ lock; } ;
struct TYPE_12__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  unk; } ;
struct TYPE_10__ {scalar_t__* Spare; } ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IWICComponentInfo ;
typedef  TYPE_2__ IEnumUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;
typedef  TYPE_3__ ComponentEnumItem ;
typedef  TYPE_4__ ComponentEnum ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 scalar_t__ CLSIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ComponentEnumVtbl ; 
 scalar_t__ CreateComponentInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 scalar_t__ HRESULT_FROM_WIN32 (scalar_t__) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IEnumUnknown_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  IEnumUnknown_Reset (TYPE_2__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct category* categories ; 
 int /*<<< orphan*/ * clsid_keyname ; 
 int /*<<< orphan*/ * instance_keyname ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

HRESULT CreateComponentEnumerator(DWORD componentTypes, DWORD options, IEnumUnknown **ppIEnumUnknown)
{
    ComponentEnum *This;
    ComponentEnumItem *item;
    const struct category *category;
    HKEY clsidkey, catidkey, instancekey;
    WCHAR guidstring[39];
    LONG res;
    int i;
    HRESULT hr=S_OK;
    CLSID clsid;

    if (options) FIXME("ignoring flags %x\n", options);

    res = RegOpenKeyExW(HKEY_CLASSES_ROOT, clsid_keyname, 0, KEY_READ, &clsidkey);
    if (res != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(res);

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(ComponentEnum));
    if (!This)
    {
        RegCloseKey(clsidkey);
        return E_OUTOFMEMORY;
    }

    This->IEnumUnknown_iface.lpVtbl = &ComponentEnumVtbl;
    This->ref = 1;
    list_init(&This->objects);
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": ComponentEnum.lock");

    for (category=categories; category->type && hr == S_OK; category++)
    {
        if ((category->type & componentTypes) == 0) continue;
        StringFromGUID2(category->catid, guidstring, 39);
        res = RegOpenKeyExW(clsidkey, guidstring, 0, KEY_READ, &catidkey);
        if (res == ERROR_SUCCESS)
        {
            res = RegOpenKeyExW(catidkey, instance_keyname, 0, KEY_READ, &instancekey);
            if (res == ERROR_SUCCESS)
            {
                i=0;
                for (;;i++)
                {
                    DWORD guidstring_size = 39;
                    res = RegEnumKeyExW(instancekey, i, guidstring, &guidstring_size, NULL, NULL, NULL, NULL);
                    if (res != ERROR_SUCCESS) break;

                    item = HeapAlloc(GetProcessHeap(), 0, sizeof(ComponentEnumItem));
                    if (!item) { hr = E_OUTOFMEMORY; break; }

                    hr = CLSIDFromString(guidstring, &clsid);
                    if (SUCCEEDED(hr))
                    {
                        hr = CreateComponentInfo(&clsid, (IWICComponentInfo**)&item->unk);
                        if (SUCCEEDED(hr))
                            list_add_tail(&This->objects, &item->entry);
                    }

                    if (FAILED(hr))
                    {
                        HeapFree(GetProcessHeap(), 0, item);
                        hr = S_OK;
                    }
                }
                RegCloseKey(instancekey);
            }
            RegCloseKey(catidkey);
        }
        if (res != ERROR_SUCCESS && res != ERROR_NO_MORE_ITEMS)
            hr = HRESULT_FROM_WIN32(res);
    }
    RegCloseKey(clsidkey);

    if (SUCCEEDED(hr))
    {
        IEnumUnknown_Reset(&This->IEnumUnknown_iface);
        *ppIEnumUnknown = &This->IEnumUnknown_iface;
    }
    else
    {
        *ppIEnumUnknown = NULL;
        IEnumUnknown_Release(&This->IEnumUnknown_iface);
    }

    return hr;
}