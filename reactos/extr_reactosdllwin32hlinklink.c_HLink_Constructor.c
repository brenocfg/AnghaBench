#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; TYPE_4__ IBindStatusCallback_iface; TYPE_3__ IDataObject_iface; TYPE_2__ IPersistStream_iface; TYPE_1__ IHlink_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_5__ HlinkImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_callback_vtbl ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dovt ; 
 TYPE_5__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  hlvt ; 
 int /*<<< orphan*/  psvt ; 

HRESULT HLink_Constructor(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    HlinkImpl * hl;

    TRACE("unkOut=%p riid=%s\n", pUnkOuter, debugstr_guid(riid));
    *ppv = NULL;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    hl = heap_alloc_zero(sizeof(HlinkImpl));
    if (!hl)
        return E_OUTOFMEMORY;

    hl->ref = 1;
    hl->IHlink_iface.lpVtbl = &hlvt;
    hl->IPersistStream_iface.lpVtbl = &psvt;
    hl->IDataObject_iface.lpVtbl = &dovt;
    hl->IBindStatusCallback_iface.lpVtbl = &bind_callback_vtbl;

    *ppv = hl;
    return S_OK;
}