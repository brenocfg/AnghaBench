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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IResourceManager_iface; } ;
typedef  TYPE_1__ ResourceManager ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IResourceManager_QueryInterface (TYPE_2__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IResourceManager_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  ResourceManager_Vtbl ; 

__attribute__((used)) static HRESULT ResourceManager_Create(REFIID riid, void **ppv)
{
    ResourceManager *This;
    HRESULT ret;

    if (!ppv) return E_INVALIDARG;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(ResourceManager));
    if (!This) return E_OUTOFMEMORY;

    This->IResourceManager_iface.lpVtbl = &ResourceManager_Vtbl;
    This->ref = 1;

    ret = IResourceManager_QueryInterface(&This->IResourceManager_iface, riid, ppv);
    IResourceManager_Release(&This->IResourceManager_iface);

    return ret;
}