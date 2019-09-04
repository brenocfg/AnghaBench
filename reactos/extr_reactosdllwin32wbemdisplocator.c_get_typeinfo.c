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
 int /*<<< orphan*/  LIBID_WbemScripting ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  LoadRegTypeLib (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wbemdisp_tid_id ; 
 int /*<<< orphan*/ ** wbemdisp_typeinfo ; 
 int /*<<< orphan*/  wbemdisp_typelib ; 

__attribute__((used)) static HRESULT get_typeinfo( enum type_id tid, ITypeInfo **ret )
{
    HRESULT hr;

    if (!wbemdisp_typelib)
    {
        ITypeLib *typelib;

        hr = LoadRegTypeLib( &LIBID_WbemScripting, 1, 2, LOCALE_SYSTEM_DEFAULT, &typelib );
        if (FAILED( hr ))
        {
            ERR( "LoadRegTypeLib failed: %08x\n", hr );
            return hr;
        }
        if (InterlockedCompareExchangePointer( (void **)&wbemdisp_typelib, typelib, NULL ))
            ITypeLib_Release( typelib );
    }
    if (!wbemdisp_typeinfo[tid])
    {
        ITypeInfo *typeinfo;

        hr = ITypeLib_GetTypeInfoOfGuid( wbemdisp_typelib, wbemdisp_tid_id[tid], &typeinfo );
        if (FAILED( hr ))
        {
            ERR( "GetTypeInfoOfGuid(%s) failed: %08x\n", debugstr_guid(wbemdisp_tid_id[tid]), hr );
            return hr;
        }
        if (InterlockedCompareExchangePointer( (void **)(wbemdisp_typeinfo + tid), typeinfo, NULL ))
            ITypeInfo_Release( typeinfo );
    }
    *ret = wbemdisp_typeinfo[tid];
    ITypeInfo_AddRef( *ret );
    return S_OK;
}