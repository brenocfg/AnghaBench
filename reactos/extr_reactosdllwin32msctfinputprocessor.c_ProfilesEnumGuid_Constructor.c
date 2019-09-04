#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int refCount; TYPE_2__ IEnumGUID_iface; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ ProfilesEnumGuid ;
typedef  TYPE_2__ IEnumGUID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnumGUIDVtbl ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  szwSystemTIPKey ; 

__attribute__((used)) static HRESULT ProfilesEnumGuid_Constructor(IEnumGUID **ppOut)
{
    ProfilesEnumGuid *This;

    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(ProfilesEnumGuid));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->IEnumGUID_iface.lpVtbl= &EnumGUIDVtbl;
    This->refCount = 1;

    if (RegCreateKeyExW(HKEY_LOCAL_MACHINE, szwSystemTIPKey, 0, NULL, 0,
                    KEY_READ | KEY_WRITE, NULL, &This->key, NULL) != ERROR_SUCCESS)
    {
        HeapFree(GetProcessHeap(), 0, This);
        return E_FAIL;
    }

    *ppOut = &This->IEnumGUID_iface;
    TRACE("returning %p\n", *ppOut);
    return S_OK;
}