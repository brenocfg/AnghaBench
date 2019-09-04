#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * doc; int /*<<< orphan*/  entry; TYPE_2__* element; TYPE_1__* sink; int /*<<< orphan*/ * plugin_unk; scalar_t__ ip_object; scalar_t__ ui_active; } ;
struct TYPE_8__ {int /*<<< orphan*/ * plugin_host; } ;
struct TYPE_7__ {int /*<<< orphan*/  IDispatch_iface; int /*<<< orphan*/ * host; int /*<<< orphan*/  cookie; int /*<<< orphan*/  iid; } ;
typedef  TYPE_3__ PluginHost ;
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  IConnectionPointContainer ;
typedef  int /*<<< orphan*/  IConnectionPoint ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IConnectionPointContainer_FindConnectionPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IConnectionPointContainer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Unadvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IConnectionPointContainer ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IOleInPlaceObject_InPlaceDeactivate (scalar_t__) ; 
 int /*<<< orphan*/  IOleInPlaceObject_UIDeactivate (scalar_t__) ; 
 int /*<<< orphan*/  IOleObject_Close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_SetClientSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  OLECLOSE_NOSAVE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_plugin_ifaces (TYPE_3__*) ; 

void detach_plugin_host(PluginHost *host)
{
    HRESULT hres;

    TRACE("%p\n", host);

    if(!host->doc)
        return;

    if(host->ip_object) {
        if(host->ui_active)
            IOleInPlaceObject_UIDeactivate(host->ip_object);
        IOleInPlaceObject_InPlaceDeactivate(host->ip_object);
    }

    if(host->plugin_unk) {
        IOleObject *ole_obj;

        hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IOleObject, (void**)&ole_obj);
        if(SUCCEEDED(hres)) {
            if(!host->ip_object)
                IOleObject_Close(ole_obj, OLECLOSE_NOSAVE);
            IOleObject_SetClientSite(ole_obj, NULL);
            IOleObject_Release(ole_obj);
        }
    }

    if(host->sink) {
        IConnectionPointContainer *cp_container;
        IConnectionPoint *cp;

        assert(host->plugin_unk != NULL);

        hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IConnectionPointContainer, (void**)&cp_container);
        if(SUCCEEDED(hres)) {
            hres = IConnectionPointContainer_FindConnectionPoint(cp_container, &host->sink->iid, &cp);
            IConnectionPointContainer_Release(cp_container);
            if(SUCCEEDED(hres)) {
                IConnectionPoint_Unadvise(cp, host->sink->cookie);
                IConnectionPoint_Release(cp);
            }
        }

        host->sink->host = NULL;
        IDispatch_Release(&host->sink->IDispatch_iface);
        host->sink = NULL;
    }

    release_plugin_ifaces(host);

    if(host->element) {
        host->element->plugin_host = NULL;
        host->element = NULL;
    }

    list_remove(&host->entry);
    list_init(&host->entry);
    host->doc = NULL;
}