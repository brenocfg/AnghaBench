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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ LoadTypeLib (scalar_t__*,int /*<<< orphan*/ **) ; 
 int MAX_PATH ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  actctx_get_typelib_module (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_get_typelib_module (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT get_typeinfo_for_iid(REFIID iid, ITypeInfo **typeinfo)
{
    WCHAR module[MAX_PATH];
    ITypeLib *typelib;
    HRESULT hr;

    *typeinfo = NULL;

    module[0] = 0;
    if (!actctx_get_typelib_module(iid, module, ARRAY_SIZE(module)))
    {
        hr = reg_get_typelib_module(iid, module, ARRAY_SIZE(module));
        if (FAILED(hr))
            return hr;
    }

    hr = LoadTypeLib(module, &typelib);
    if (hr != S_OK) {
        ERR("Failed to load typelib for %s, but it should be there.\n", debugstr_guid(iid));
        return hr;
    }

    hr = ITypeLib_GetTypeInfoOfGuid(typelib, iid, typeinfo);
    ITypeLib_Release(typelib);
    if (hr != S_OK)
        ERR("typelib does not contain info for %s\n", debugstr_guid(iid));

    return hr;
}