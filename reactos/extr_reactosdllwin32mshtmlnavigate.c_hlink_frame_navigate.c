#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  IBindStatusCallback_iface; int /*<<< orphan*/  request_data; } ;
struct TYPE_11__ {TYPE_2__ bsc; } ;
typedef  TYPE_3__ nsChannelBSC ;
struct TYPE_12__ {int /*<<< orphan*/  request_headers; int /*<<< orphan*/  post_data_contains_headers; int /*<<< orphan*/  post_data_stream; } ;
typedef  TYPE_4__ nsChannel ;
typedef  char WCHAR ;
struct TYPE_13__ {TYPE_1__* doc_obj; } ;
struct TYPE_9__ {scalar_t__ client; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHlinkFrame ;
typedef  int /*<<< orphan*/  IHlink ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  TYPE_5__ HTMLDocument ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_StdHlink ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateAsyncBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  HLINKSETF_TARGET ; 
 int HLNF_OPENINNEWWINDOW ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHlinkFrame_Navigate (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlinkFrame_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlink_SetMonikerReference (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlink_SetTargetFrameName (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  IID_IHlink ; 
 int /*<<< orphan*/  IID_IHlinkFrame ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ create_channelbsc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_3__**) ; 
 scalar_t__ do_query_service (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  read_post_data_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT hlink_frame_navigate(HTMLDocument *doc, LPCWSTR url, nsChannel *nschannel, DWORD hlnf, BOOL *cancel)
{
    IHlinkFrame *hlink_frame;
    nsChannelBSC *callback;
    IBindCtx *bindctx;
    IMoniker *mon;
    IHlink *hlink;
    HRESULT hres;

    *cancel = FALSE;

    hres = do_query_service((IUnknown*)doc->doc_obj->client, &IID_IHlinkFrame, &IID_IHlinkFrame,
            (void**)&hlink_frame);
    if(FAILED(hres))
        return S_OK;

    hres = create_channelbsc(NULL, NULL, NULL, 0, FALSE, &callback);
    if(FAILED(hres)) {
        IHlinkFrame_Release(hlink_frame);
        return hres;
    }

    if(nschannel)
        read_post_data_stream(nschannel->post_data_stream, nschannel->post_data_contains_headers,
                &nschannel->request_headers, &callback->bsc.request_data);

    hres = CreateAsyncBindCtx(0, &callback->bsc.IBindStatusCallback_iface, NULL, &bindctx);
    if(SUCCEEDED(hres))
       hres = CoCreateInstance(&CLSID_StdHlink, NULL, CLSCTX_INPROC_SERVER,
                &IID_IHlink, (LPVOID*)&hlink);

    if(SUCCEEDED(hres))
        hres = CreateURLMoniker(NULL, url, &mon);

    if(SUCCEEDED(hres)) {
        IHlink_SetMonikerReference(hlink, HLINKSETF_TARGET, mon, NULL);

        if(hlnf & HLNF_OPENINNEWWINDOW) {
            static const WCHAR wszBlank[] = {'_','b','l','a','n','k',0};
            IHlink_SetTargetFrameName(hlink, wszBlank); /* FIXME */
        }

        hres = IHlinkFrame_Navigate(hlink_frame, hlnf, bindctx,
                &callback->bsc.IBindStatusCallback_iface, hlink);
        IMoniker_Release(mon);
        *cancel = hres == S_OK;
        hres = S_OK;
    }

    IHlinkFrame_Release(hlink_frame);
    IBindCtx_Release(bindctx);
    IBindStatusCallback_Release(&callback->bsc.IBindStatusCallback_iface);
    return hres;
}