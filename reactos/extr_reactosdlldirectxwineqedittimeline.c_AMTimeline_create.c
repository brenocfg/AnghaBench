#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int ref; TYPE_3__ IUnknown_inner; TYPE_3__* outer_unk; TYPE_1__ IAMTimeline_iface; } ;
typedef  TYPE_2__ TimelineImpl ;
typedef  TYPE_3__* LPVOID ;
typedef  TYPE_3__ IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 TYPE_2__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IAMTimeline_VTable ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  timeline_vtbl ; 

HRESULT AMTimeline_create(IUnknown *pUnkOuter, LPVOID *ppv)
{
    TimelineImpl* obj = NULL;

    TRACE("(%p,%p)\n", pUnkOuter, ppv);

    obj = CoTaskMemAlloc(sizeof(TimelineImpl));
    if (NULL == obj) {
        *ppv = NULL;
        return E_OUTOFMEMORY;
    }
    ZeroMemory(obj, sizeof(TimelineImpl));

    obj->ref = 1;
    obj->IUnknown_inner.lpVtbl = &timeline_vtbl;
    obj->IAMTimeline_iface.lpVtbl = &IAMTimeline_VTable;

    if (pUnkOuter)
        obj->outer_unk = pUnkOuter;
    else
        obj->outer_unk = &obj->IUnknown_inner;

    *ppv = &obj->IUnknown_inner;
    return S_OK;
}