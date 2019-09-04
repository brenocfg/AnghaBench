#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum tid_t { ____Placeholder_tid_t } tid_t ;
struct TYPE_2__ {int /*<<< orphan*/  major; int /*<<< orphan*/  iid; } ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 size_t LibXml ; 
 int /*<<< orphan*/  LoadRegTypeLib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_OK ; 
 unsigned int get_libid_from_tid (int) ; 
 int /*<<< orphan*/  get_riid_from_tid (int) ; 
 TYPE_1__* lib_ids ; 
 int /*<<< orphan*/ ** typeinfos ; 
 int /*<<< orphan*/ * typelib ; 

HRESULT get_typeinfo(enum tid_t tid, ITypeInfo **typeinfo)
{
    unsigned lib = get_libid_from_tid(tid);
    HRESULT hres;

    if(!typelib[lib]) {
        ITypeLib *tl;

        hres = LoadRegTypeLib(lib_ids[lib].iid, lib_ids[lib].major, 0, LOCALE_SYSTEM_DEFAULT, &tl);
        if(FAILED(hres)) {
            ERR("LoadRegTypeLib failed: %08x\n", hres);
            return hres;
        }

        if(InterlockedCompareExchangePointer((void**)&typelib[lib], tl, NULL))
            ITypeLib_Release(tl);
    }

    if(!typeinfos[tid]) {
        ITypeInfo *ti;

        hres = ITypeLib_GetTypeInfoOfGuid(typelib[lib], get_riid_from_tid(tid), &ti);
        if(FAILED(hres)) {
            /* try harder with typelib from msxml.dll */
            hres = ITypeLib_GetTypeInfoOfGuid(typelib[LibXml], get_riid_from_tid(tid), &ti);
            if(FAILED(hres)) {
                ERR("GetTypeInfoOfGuid failed: %08x\n", hres);
                return hres;
            }
        }

        if(InterlockedCompareExchangePointer((void**)(typeinfos+tid), ti, NULL))
            ITypeInfo_Release(ti);
    }

    *typeinfo = typeinfos[tid];

    ITypeInfo_AddRef(typeinfos[tid]);
    return S_OK;
}