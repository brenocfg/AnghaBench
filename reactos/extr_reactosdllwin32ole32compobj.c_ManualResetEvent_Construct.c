#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; TYPE_3__ ISynchronize_iface; int /*<<< orphan*/  event; TYPE_1__ ISynchronizeHandle_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_2__ MREImpl ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISynchronize_QueryInterface (TYPE_3__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  ISynchronize_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  SynchronizeHandleVtbl ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  vt_ISynchronize ; 

__attribute__((used)) static HRESULT ManualResetEvent_Construct(IUnknown *punkouter, REFIID iid, void **ppv)
{
    MREImpl *This = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MREImpl));
    HRESULT hr;

    if(punkouter)
        FIXME("Aggregation not implemented.\n");

    This->ref = 1;
    This->ISynchronize_iface.lpVtbl = &vt_ISynchronize;
    This->ISynchronizeHandle_iface.lpVtbl = &SynchronizeHandleVtbl;
    This->event = CreateEventW(NULL, TRUE, FALSE, NULL);

    hr = ISynchronize_QueryInterface(&This->ISynchronize_iface, iid, ppv);
    ISynchronize_Release(&This->ISynchronize_iface);
    return hr;
}