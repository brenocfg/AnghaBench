#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_28__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_27__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_26__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_25__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_24__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_23__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_22__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_21__ {int /*<<< orphan*/  nselem; } ;
struct TYPE_20__ {int /*<<< orphan*/  plugin_hosts; } ;
struct TYPE_19__ {TYPE_10__* plugin_host; TYPE_1__ element; } ;
struct TYPE_18__ {int ref; TYPE_11__* element; int /*<<< orphan*/  entry; TYPE_12__* doc; int /*<<< orphan*/  clsid; int /*<<< orphan*/ * plugin_unk; TYPE_9__ IServiceProvider_iface; TYPE_8__ IBindHost_iface; TYPE_7__ IOleControlSite_iface; TYPE_6__ IOleInPlaceSiteEx_iface; TYPE_5__ IDispatch_iface; TYPE_4__ IPropertyNotifySink_iface; TYPE_3__ IAdviseSinkEx_iface; TYPE_2__ IOleClientSite_iface; } ;
typedef  TYPE_10__ PluginHost ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_11__ HTMLPluginContainer ;
typedef  TYPE_12__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  AdviseSinkExVtbl ; 
 int /*<<< orphan*/  BindHostVtbl ; 
 int /*<<< orphan*/  DispatchVtbl ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleClientSiteVtbl ; 
 int /*<<< orphan*/  OleControlSiteVtbl ; 
 int /*<<< orphan*/  OleInPlaceSiteExVtbl ; 
 int /*<<< orphan*/  PropertyNotifySinkVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ServiceProviderVtbl ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * create_activex_object (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_10__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  initialize_plugin_object (TYPE_10__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT create_plugin_host(HTMLDocumentNode *doc, HTMLPluginContainer *container)
{
    PluginHost *host;
    IUnknown *unk;
    CLSID clsid;

    assert(!container->plugin_host);

    unk = create_activex_object(doc, container->element.nselem, &clsid);
    if(!unk)
        return E_FAIL;

    host = heap_alloc_zero(sizeof(*host));
    if(!host) {
        IUnknown_Release(unk);
        return E_OUTOFMEMORY;
    }

    host->IOleClientSite_iface.lpVtbl      = &OleClientSiteVtbl;
    host->IAdviseSinkEx_iface.lpVtbl       = &AdviseSinkExVtbl;
    host->IPropertyNotifySink_iface.lpVtbl = &PropertyNotifySinkVtbl;
    host->IDispatch_iface.lpVtbl           = &DispatchVtbl;
    host->IOleInPlaceSiteEx_iface.lpVtbl   = &OleInPlaceSiteExVtbl;
    host->IOleControlSite_iface.lpVtbl     = &OleControlSiteVtbl;
    host->IBindHost_iface.lpVtbl           = &BindHostVtbl;
    host->IServiceProvider_iface.lpVtbl    = &ServiceProviderVtbl;

    host->ref = 1;

    host->plugin_unk = unk;
    host->clsid = clsid;

    host->doc = doc;
    list_add_tail(&doc->plugin_hosts, &host->entry);

    container->plugin_host = host;
    host->element = container;

    initialize_plugin_object(host);

    return S_OK;
}