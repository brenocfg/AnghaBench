#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/  IUnknown_iface; } ;
struct TYPE_27__ {int cbSize; int dwOptions; } ;
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {TYPE_5__* DebugInfo; } ;
struct TYPE_24__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_23__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_22__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_21__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_26__ {int ref; int report_mime; int bindf; TYPE_14__ IBinding_iface; TYPE_9__* stgmed_buf; int /*<<< orphan*/ * stgmed_obj; TYPE_12__* protocol; int /*<<< orphan*/  clipboard_format; int /*<<< orphan*/  url; int /*<<< orphan*/  use_cache_file; TYPE_8__ bindinfo; int /*<<< orphan*/  callback; int /*<<< orphan*/  service_provider; TYPE_13__ section; int /*<<< orphan*/ * mon; int /*<<< orphan*/ * bctx; int /*<<< orphan*/  download_state; int /*<<< orphan*/  notif_hwnd; int /*<<< orphan*/  iid; scalar_t__ to_object; TYPE_4__ IServiceProvider_iface; TYPE_3__ IWinInetHttpInfo_iface; TYPE_2__ IInternetBindInfo_iface; TYPE_1__ IInternetProtocolSink_iface; } ;
struct TYPE_25__ {scalar_t__* Spare; } ;
struct TYPE_18__ {int /*<<< orphan*/  IInternetProtocolEx_iface; } ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  TYPE_6__ Binding ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  BINDINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BEFORE_DOWNLOAD ; 
 int BINDF_ASYNCHRONOUS ; 
 int BINDF_FROMURLMON ; 
 int BINDF_NEEDFILE ; 
 int BINDF_PULLDATA ; 
 int /*<<< orphan*/  BindingVtbl ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindCtx_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindStatusCallback_GetBindInfo (int /*<<< orphan*/ ,int*,TYPE_8__*) ; 
 int /*<<< orphan*/  IBindStatusCallback_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IBinding_Release (TYPE_14__*) ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IID_IStream ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IInternetProtocolEx_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_GetDisplayUri (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_13__*) ; 
 int /*<<< orphan*/  InternetBindInfoVtbl ; 
 int /*<<< orphan*/  InternetProtocolSinkVtbl ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ServiceProviderVtbl ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  URLMON_LockModule () ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  WinInetHttpInfoVtbl ; 
 int /*<<< orphan*/  create_binding_protocol (TYPE_12__**) ; 
 TYPE_9__* create_stgmed_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_stgmed_file (TYPE_9__*) ; 
 int /*<<< orphan*/ * create_stgmed_stream (TYPE_9__*) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_BINDINFO (TYPE_8__*) ; 
 int /*<<< orphan*/  get_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_notif_hwnd () ; 
 TYPE_6__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  is_urlmon_protocol (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Binding_Create(IMoniker *mon, Binding *binding_ctx, IUri *uri, IBindCtx *pbc,
        BOOL to_obj, REFIID riid, Binding **binding)
{
    Binding *ret;
    HRESULT hres;

    URLMON_LockModule();

    ret = heap_alloc_zero(sizeof(Binding));

    ret->IBinding_iface.lpVtbl = &BindingVtbl;
    ret->IInternetProtocolSink_iface.lpVtbl = &InternetProtocolSinkVtbl;
    ret->IInternetBindInfo_iface.lpVtbl = &InternetBindInfoVtbl;
    ret->IWinInetHttpInfo_iface.lpVtbl = &WinInetHttpInfoVtbl;
    ret->IServiceProvider_iface.lpVtbl = &ServiceProviderVtbl;

    ret->ref = 1;

    ret->to_object = to_obj;
    ret->iid = *riid;
    ret->notif_hwnd = get_notif_hwnd();
    ret->report_mime = !binding_ctx;
    ret->download_state = BEFORE_DOWNLOAD;

    if(to_obj) {
        IBindCtx_AddRef(pbc);
        ret->bctx = pbc;
    }

    if(mon) {
        IMoniker_AddRef(mon);
        ret->mon = mon;
    }

    ret->bindinfo.cbSize = sizeof(BINDINFO);

    InitializeCriticalSection(&ret->section);
    ret->section.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": Binding.section");

    hres = get_callback(pbc, &ret->callback);
    if(FAILED(hres)) {
        WARN("Could not get IBindStatusCallback\n");
        IBinding_Release(&ret->IBinding_iface);
        return hres;
    }

    IBindStatusCallback_QueryInterface(ret->callback, &IID_IServiceProvider,
                                       (void**)&ret->service_provider);

    if(binding_ctx) {
        ret->protocol = binding_ctx->protocol;
        IInternetProtocolEx_AddRef(&ret->protocol->IInternetProtocolEx_iface);
    }else {
        hres = create_binding_protocol(&ret->protocol);
        if(FAILED(hres)) {
            WARN("Could not get protocol handler\n");
            IBinding_Release(&ret->IBinding_iface);
            return hres;
        }
    }

    hres = IBindStatusCallback_GetBindInfo(ret->callback, &ret->bindf, &ret->bindinfo);
    if(FAILED(hres)) {
        WARN("GetBindInfo failed: %08x\n", hres);
        IBinding_Release(&ret->IBinding_iface);
        return hres;
    }

    TRACE("bindf %08x\n", ret->bindf);
    dump_BINDINFO(&ret->bindinfo);

    ret->bindf |= BINDF_FROMURLMON;
    if(to_obj)
        ret->bindinfo.dwOptions |= 0x100000;

    if(!(ret->bindf & BINDF_ASYNCHRONOUS) || !(ret->bindf & BINDF_PULLDATA)) {
        ret->bindf |= BINDF_NEEDFILE;
        ret->use_cache_file = TRUE;
    }else if(!is_urlmon_protocol(uri)) {
        ret->bindf |= BINDF_NEEDFILE;
    }

    hres = IUri_GetDisplayUri(uri, &ret->url);
    if(FAILED(hres)) {
        IBinding_Release(&ret->IBinding_iface);
        return hres;
    }

    if(binding_ctx) {
        ret->stgmed_buf = binding_ctx->stgmed_buf;
        IUnknown_AddRef(&ret->stgmed_buf->IUnknown_iface);
        ret->clipboard_format = binding_ctx->clipboard_format;
    }else {
        ret->stgmed_buf = create_stgmed_buf(&ret->protocol->IInternetProtocolEx_iface);
    }

    if(to_obj) {
        ret->stgmed_obj = NULL;
    }else if(IsEqualGUID(&IID_IStream, riid)) {
        ret->stgmed_obj = create_stgmed_stream(ret->stgmed_buf);
    }else if(IsEqualGUID(&IID_IUnknown, riid)) {
        ret->bindf |= BINDF_NEEDFILE;
        ret->stgmed_obj = create_stgmed_file(ret->stgmed_buf);
    }else {
        FIXME("Unsupported riid %s\n", debugstr_guid(riid));
        IBinding_Release(&ret->IBinding_iface);
        return E_NOTIMPL;
    }

    *binding = ret;
    return S_OK;
}