#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
struct TYPE_12__ {int /*<<< orphan*/  nsIAsyncVerifyRedirectCallback_iface; TYPE_5__* nschannel; } ;
typedef  TYPE_1__ nsRedirectCallback ;
typedef  int /*<<< orphan*/  nsIChannelEventSink ;
typedef  int /*<<< orphan*/  nsIChannel ;
struct TYPE_13__ {TYPE_5__* nschannel; } ;
typedef  TYPE_2__ nsChannelBSC ;
struct TYPE_14__ {int /*<<< orphan*/  nsIHttpChannel_iface; } ;
typedef  TYPE_3__ nsChannel ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_15__ {int /*<<< orphan*/  nsIHttpChannel_iface; int /*<<< orphan*/  notif_callback; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IID_nsIChannelEventSink ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REDIRECT_TEMPORARY ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,TYPE_5__*,...) ; 
 int /*<<< orphan*/  create_redirect_callback (TYPE_3__*,TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  create_redirect_nschannel (int /*<<< orphan*/  const*,TYPE_5__*,TYPE_3__**) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIAsyncVerifyRedirectCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIChannelEventSink_AsyncOnChannelRedirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIChannelEventSink_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIHttpChannel_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIInterfaceRequestor_GetInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static HRESULT handle_redirect(nsChannelBSC *This, const WCHAR *new_url)
{
    nsRedirectCallback *callback;
    nsIChannelEventSink *sink;
    nsChannel *new_channel;
    nsresult nsres;
    HRESULT hres;

    TRACE("(%p)->(%s)\n", This, debugstr_w(new_url));

    if(!This->nschannel || !This->nschannel->notif_callback)
        return S_OK;

    nsres = nsIInterfaceRequestor_GetInterface(This->nschannel->notif_callback, &IID_nsIChannelEventSink, (void**)&sink);
    if(NS_FAILED(nsres))
        return S_OK;

    hres = create_redirect_nschannel(new_url, This->nschannel, &new_channel);
    if(SUCCEEDED(hres)) {
        TRACE("%p %p->%p\n", This, This->nschannel, new_channel);

        hres = create_redirect_callback(new_channel, This, &callback);
        nsIHttpChannel_Release(&new_channel->nsIHttpChannel_iface);
    }

    if(SUCCEEDED(hres)) {
        nsres = nsIChannelEventSink_AsyncOnChannelRedirect(sink, (nsIChannel*)&This->nschannel->nsIHttpChannel_iface,
                (nsIChannel*)&callback->nschannel->nsIHttpChannel_iface, REDIRECT_TEMPORARY, /* FIXME */
                &callback->nsIAsyncVerifyRedirectCallback_iface);

        if(NS_FAILED(nsres))
            FIXME("AsyncOnChannelRedirect failed: %08x\n", hres);
        else if(This->nschannel != callback->nschannel)
            FIXME("nschannel not updated\n");

        nsIAsyncVerifyRedirectCallback_Release(&callback->nsIAsyncVerifyRedirectCallback_iface);
    }

    nsIChannelEventSink_Release(sink);
    return hres;
}