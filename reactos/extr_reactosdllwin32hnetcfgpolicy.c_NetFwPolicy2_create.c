#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int refs; int /*<<< orphan*/  fw_policy2_rules; TYPE_1__ INetFwPolicy2_iface; } ;
typedef  TYPE_2__ fw_policy2 ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,void*,...) ; 
 int /*<<< orphan*/  create_INetFwRules (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_policy2_vtbl ; 

HRESULT NetFwPolicy2_create( IUnknown *outer, void **obj )
{
    fw_policy2 *fp;

    TRACE("(%p,%p)\n", outer, obj);

    fp = HeapAlloc( GetProcessHeap(), 0, sizeof(*fp) );
    if (!fp) return E_OUTOFMEMORY;

    fp->INetFwPolicy2_iface.lpVtbl = &fw_policy2_vtbl;
    fp->refs = 1;

    *obj = &fp->INetFwPolicy2_iface;

    if (FAILED(create_INetFwRules(&fp->fw_policy2_rules)))
    {
        HeapFree( GetProcessHeap(), 0, fp );
        return E_OUTOFMEMORY;
    }

    TRACE("returning iface %p\n", *obj);
    return S_OK;
}