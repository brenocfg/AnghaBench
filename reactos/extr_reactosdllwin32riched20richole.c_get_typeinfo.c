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
typedef  enum tid_t { ____Placeholder_tid_t } tid_t ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_typelib () ; 
 int /*<<< orphan*/ * tid_ids ; 
 int /*<<< orphan*/ ** typeinfos ; 
 int /*<<< orphan*/  typelib ; 

__attribute__((used)) static HRESULT get_typeinfo(enum tid_t tid, ITypeInfo **typeinfo)
{
    HRESULT hr;

    if (!typelib)
        hr = load_typelib();
    if (!typelib)
        return hr;

    if (!typeinfos[tid])
    {
        ITypeInfo *ti;

        hr = ITypeLib_GetTypeInfoOfGuid(typelib, tid_ids[tid], &ti);
        if (FAILED(hr))
        {
            ERR("GetTypeInfoOfGuid(%s) failed: %08x\n", debugstr_guid(tid_ids[tid]), hr);
            return hr;
        }

        if (InterlockedCompareExchangePointer((void**)(typeinfos+tid), ti, NULL))
            ITypeInfo_Release(ti);
    }

    *typeinfo = typeinfos[tid];
    return S_OK;
}