#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int ref; TYPE_8__ nsIWebBrowserChrome_iface; int /*<<< orphan*/ * doc; TYPE_6__ nsISupportsWeakReference_iface; TYPE_5__ nsIInterfaceRequestor_iface; TYPE_4__ nsITooltipListener_iface; TYPE_3__ nsIEmbeddingSiteWindow_iface; TYPE_2__ nsIURIContentListener_iface; TYPE_1__ nsIContextMenuListener_iface; } ;
typedef  TYPE_7__ NSContainer ;
typedef  int /*<<< orphan*/  HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_CLASSNOTAVAILABLE ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 TYPE_7__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_nscontainer (TYPE_7__*) ; 
 int /*<<< orphan*/  load_gecko () ; 
 int /*<<< orphan*/  nsContextMenuListenerVtbl ; 
 int /*<<< orphan*/  nsEmbeddingSiteWindowVtbl ; 
 int /*<<< orphan*/  nsIWebBrowserChrome_Release (TYPE_8__*) ; 
 int /*<<< orphan*/  nsInterfaceRequestorVtbl ; 
 int /*<<< orphan*/  nsSupportsWeakReferenceVtbl ; 
 int /*<<< orphan*/  nsTooltipListenerVtbl ; 
 int /*<<< orphan*/  nsURIContentListenerVtbl ; 
 int /*<<< orphan*/  nsWebBrowserChromeVtbl ; 

HRESULT create_nscontainer(HTMLDocumentObj *doc, NSContainer **_ret)
{
    NSContainer *ret;
    HRESULT hres;

    if(!load_gecko())
        return CLASS_E_CLASSNOTAVAILABLE;

    ret = heap_alloc_zero(sizeof(NSContainer));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->nsIWebBrowserChrome_iface.lpVtbl = &nsWebBrowserChromeVtbl;
    ret->nsIContextMenuListener_iface.lpVtbl = &nsContextMenuListenerVtbl;
    ret->nsIURIContentListener_iface.lpVtbl = &nsURIContentListenerVtbl;
    ret->nsIEmbeddingSiteWindow_iface.lpVtbl = &nsEmbeddingSiteWindowVtbl;
    ret->nsITooltipListener_iface.lpVtbl = &nsTooltipListenerVtbl;
    ret->nsIInterfaceRequestor_iface.lpVtbl = &nsInterfaceRequestorVtbl;
    ret->nsISupportsWeakReference_iface.lpVtbl = &nsSupportsWeakReferenceVtbl;

    ret->doc = doc;
    ret->ref = 1;

    hres = init_nscontainer(ret);
    if(SUCCEEDED(hres))
        *_ret = ret;
    else
        nsIWebBrowserChrome_Release(&ret->nsIWebBrowserChrome_iface);
    return hres;
}