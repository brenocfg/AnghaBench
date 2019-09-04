#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int ref; int is_dispiface; int /*<<< orphan*/  cookie; TYPE_1__ IDispatch_iface; int /*<<< orphan*/ * typeinfo; int /*<<< orphan*/  iid; TYPE_3__* host; } ;
struct TYPE_12__ {int /*<<< orphan*/  plugin_unk; } ;
struct TYPE_11__ {scalar_t__ typekind; int /*<<< orphan*/  guid; } ;
typedef  scalar_t__ TYPEKIND ;
typedef  TYPE_2__ TYPEATTR ;
typedef  TYPE_3__ PluginHost ;
typedef  TYPE_4__ PHEventSink ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  IConnectionPointContainer ;
typedef  int /*<<< orphan*/  IConnectionPoint ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IConnectionPointContainer_FindConnectionPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IConnectionPointContainer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IConnectionPoint_Advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IConnectionPoint_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IConnectionPointContainer ; 
 int /*<<< orphan*/  ITypeInfo_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  PHCPDispatchVtbl ; 
 scalar_t__ TKIND_DISPATCH ; 
 scalar_t__ TKIND_INTERFACE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 scalar_t__ debugstr_guid (int /*<<< orphan*/ *) ; 
 TYPE_4__* heap_alloc_zero (int) ; 

__attribute__((used)) static PHEventSink *create_event_sink(PluginHost *plugin_host, ITypeInfo *typeinfo)
{
    IConnectionPointContainer *cp_container;
    PHEventSink *ret;
    IConnectionPoint *cp;
    TYPEATTR *typeattr;
    TYPEKIND typekind;
    GUID guid;
    HRESULT hres;

    hres = ITypeInfo_GetTypeAttr(typeinfo, &typeattr);
    if(FAILED(hres))
        return NULL;

    typekind = typeattr->typekind;
    guid = typeattr->guid;
    ITypeInfo_ReleaseTypeAttr(typeinfo, typeattr);

    TRACE("guid %s typekind %d\n", debugstr_guid(&guid), typekind);

    if(typekind != TKIND_INTERFACE && typekind != TKIND_DISPATCH) {
        WARN("invalid typekind %d\n", typekind);
        return NULL;
    }

    hres = IUnknown_QueryInterface(plugin_host->plugin_unk, &IID_IConnectionPointContainer, (void**)&cp_container);
    if(FAILED(hres)) {
        WARN("Could not get IConnectionPointContainer iface: %08x\n", hres);
        return NULL;
    }

    hres = IConnectionPointContainer_FindConnectionPoint(cp_container, &guid, &cp);
    IConnectionPointContainer_Release(cp_container);
    if(FAILED(hres)) {
        WARN("Could not find %s connection point\n", debugstr_guid(&guid));
        return NULL;
    }

    ret = heap_alloc_zero(sizeof(*ret));
    if(ret) {
        ret->IDispatch_iface.lpVtbl = &PHCPDispatchVtbl;
        ret->ref = 1;
        ret->host = plugin_host;
        ret->iid = guid;
        ret->is_dispiface = typekind == TKIND_DISPATCH;

        ITypeInfo_AddRef(typeinfo);
        ret->typeinfo = typeinfo;

        hres = IConnectionPoint_Advise(cp, (IUnknown*)&ret->IDispatch_iface, &ret->cookie);
    }else {
        hres = E_OUTOFMEMORY;
    }

    IConnectionPoint_Release(cp);
    if(FAILED(hres)) {
        WARN("Advise failed: %08x\n", hres);
        return NULL;
    }

    return ret;
}