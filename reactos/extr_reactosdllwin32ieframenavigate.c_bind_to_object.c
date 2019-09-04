#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  IOleClientSite_iface; } ;
typedef  int /*<<< orphan*/  LPOLESTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindCtx_RegisterObjectParam (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IMoniker_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ SZ_HTML_CLIENTSITE_OBJECTPARAM ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  create_moniker (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_dochost_url (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ try_application_url (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT bind_to_object(DocHost *This, IMoniker *mon, LPCWSTR url, IBindCtx *bindctx,
                              IBindStatusCallback *callback)
{
    IUnknown *unk = NULL;
    WCHAR *display_name;
    HRESULT hres;

    if(mon) {
        IMoniker_AddRef(mon);
    }else {
        hres = create_moniker(url, &mon);
        if(FAILED(hres))
            return hres;
    }

    hres = IMoniker_GetDisplayName(mon, 0, NULL, &display_name);
    if(FAILED(hres)) {
        FIXME("GetDisplayName failed: %08x\n", hres);
        IMoniker_Release(mon);
        return hres;
    }

    hres = set_dochost_url(This, display_name);
    CoTaskMemFree(display_name);
    if(FAILED(hres)) {
        IMoniker_Release(mon);
        return hres;
    }

    IBindCtx_RegisterObjectParam(bindctx, (LPOLESTR)SZ_HTML_CLIENTSITE_OBJECTPARAM,
                                 (IUnknown*)&This->IOleClientSite_iface);

    hres = IMoniker_BindToObject(mon, bindctx, NULL, &IID_IUnknown, (void**)&unk);
    if(SUCCEEDED(hres)) {
        hres = S_OK;
        if(unk)
            IUnknown_Release(unk);
    }else if(try_application_url(url)) {
        hres = S_OK;
    }else {
        FIXME("BindToObject failed: %08x\n", hres);
    }

    IMoniker_Release(mon);
    return S_OK;
}