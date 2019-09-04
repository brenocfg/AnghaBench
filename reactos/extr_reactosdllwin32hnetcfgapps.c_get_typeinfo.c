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
typedef  enum type_id { ____Placeholder_type_id } type_id ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIBID_NetFwPublicTypeLib ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  LoadRegTypeLib (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tid_id ; 
 int /*<<< orphan*/ ** typeinfo ; 
 int /*<<< orphan*/  typelib ; 

HRESULT get_typeinfo( enum type_id tid, ITypeInfo **ret )
{
    HRESULT hr;

    if (!typelib)
    {
        ITypeLib *lib;

        hr = LoadRegTypeLib( &LIBID_NetFwPublicTypeLib, 1, 0, LOCALE_SYSTEM_DEFAULT, &lib );
        if (FAILED(hr))
        {
            ERR("LoadRegTypeLib failed: %08x\n", hr);
            return hr;
        }
        if (InterlockedCompareExchangePointer( (void **)&typelib, lib, NULL ))
            ITypeLib_Release( lib );
    }
    if (!typeinfo[tid])
    {
        ITypeInfo *info;

        hr = ITypeLib_GetTypeInfoOfGuid( typelib, tid_id[tid], &info );
        if (FAILED(hr))
        {
            ERR("GetTypeInfoOfGuid(%s) failed: %08x\n", debugstr_guid(tid_id[tid]), hr);
            return hr;
        }
        if (InterlockedCompareExchangePointer( (void **)(typeinfo + tid), info, NULL ))
            ITypeInfo_Release( info );
    }
    *ret = typeinfo[tid];
    ITypeInfo_AddRef(typeinfo[tid]);
    return S_OK;
}