#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bindinfo ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_16__ {int /*<<< orphan*/ * hGlobal; } ;
struct TYPE_17__ {TYPE_1__ u; } ;
struct TYPE_20__ {int cbSize; scalar_t__ dwBindVerb; TYPE_2__ stgmedData; scalar_t__ cbstgmedData; } ;
struct TYPE_19__ {int /*<<< orphan*/  IBindStatusCallback_iface; } ;
struct TYPE_18__ {scalar_t__ doc_navigate; } ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHttpNegotiate ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ DocHost ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_4__ BindStatusCallback ;
typedef  TYPE_5__ BINDINFO ;

/* Variables and functions */
 scalar_t__ BINDVERB_POST ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindStatusCallback_GetBindInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  IBindStatusCallback_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHttpNegotiate_BeginningTransaction (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHttpNegotiate_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHttpNegotiate ; 
 int /*<<< orphan*/  IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ReleaseBindInfo (TYPE_5__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  async_doc_navigate (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_4__* create_callback (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_BINDINFO (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  navigate_bsc (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT navigate_hlink(DocHost *This, IMoniker *mon, IBindCtx *bindctx,
                              IBindStatusCallback *callback)
{
    IHttpNegotiate *http_negotiate;
    BindStatusCallback *bsc;
    PBYTE post_data = NULL;
    ULONG post_data_len = 0;
    LPWSTR headers = NULL, url;
    BINDINFO bindinfo;
    DWORD bindf = 0;
    HRESULT hres;

    TRACE("\n");

    hres = IMoniker_GetDisplayName(mon, 0, NULL, &url);
    if(FAILED(hres))
        FIXME("GetDisplayName failed: %08x\n", hres);

    hres = IBindStatusCallback_QueryInterface(callback, &IID_IHttpNegotiate,
                                              (void**)&http_negotiate);
    if(SUCCEEDED(hres)) {
        static const WCHAR null_string[] = {0};

        IHttpNegotiate_BeginningTransaction(http_negotiate, null_string, null_string, 0,
                                            &headers);
        IHttpNegotiate_Release(http_negotiate);
    }

    memset(&bindinfo, 0, sizeof(bindinfo));
    bindinfo.cbSize = sizeof(bindinfo);

    hres = IBindStatusCallback_GetBindInfo(callback, &bindf, &bindinfo);
    dump_BINDINFO(&bindinfo);
    if(bindinfo.dwBindVerb == BINDVERB_POST) {
        post_data_len = bindinfo.cbstgmedData;
        if(post_data_len)
            post_data = bindinfo.stgmedData.u.hGlobal;
    }

    if(This->doc_navigate) {
        hres = async_doc_navigate(This, url, headers, post_data, post_data_len, FALSE);
    }else {
        bsc = create_callback(This, url, post_data, post_data_len, headers);
        hres = navigate_bsc(This, bsc, mon);
        IBindStatusCallback_Release(&bsc->IBindStatusCallback_iface);
    }

    CoTaskMemFree(url);
    CoTaskMemFree(headers);
    ReleaseBindInfo(&bindinfo);

    return hres;
}