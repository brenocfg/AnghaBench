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
struct TYPE_5__ {int ref; TYPE_2__ IClassFactory_iface; int /*<<< orphan*/  clsid; } ;
typedef  int /*<<< orphan*/  IID ;
typedef  TYPE_1__ IClassFactoryImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IClassFactory_QueryInterface (TYPE_2__*,int /*<<< orphan*/  const*,void**) ; 
 int /*<<< orphan*/  IClassFactory_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  iclassfact ; 

__attribute__((used)) static HRESULT AVIFILE_CreateClassFactory(const CLSID *clsid, const IID *riid, void **ppv)
{
    IClassFactoryImpl *cf;
    HRESULT hr;

    *ppv = NULL;

    cf = HeapAlloc(GetProcessHeap(), 0, sizeof(*cf));
    if (!cf)
        return E_OUTOFMEMORY;

    cf->IClassFactory_iface.lpVtbl = &iclassfact;
    cf->ref = 1;
    cf->clsid = *clsid;

    hr = IClassFactory_QueryInterface(&cf->IClassFactory_iface, riid, ppv);
    IClassFactory_Release(&cf->IClassFactory_iface);

    return hr;
}