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
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  REFGUID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IServiceProvider ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IServiceProvider_QueryService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IServiceProvider_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

HRESULT do_query_service(IUnknown *unk, REFGUID guid_service, REFIID riid, void **ppv)
{
    IServiceProvider *sp;
    HRESULT hres;

    hres = IUnknown_QueryInterface(unk, &IID_IServiceProvider, (void**)&sp);
    if(FAILED(hres))
        return hres;

    hres = IServiceProvider_QueryService(sp, guid_service, riid, ppv);
    IServiceProvider_Release(sp);
    return hres;
}