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
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pMarshal; scalar_t__ ref; TYPE_2__ IROTData_iface; TYPE_1__ IMoniker_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ AntiMonikerImpl ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  VT_AntiMonikerImpl ; 
 int /*<<< orphan*/  VT_ROTDataImpl ; 

__attribute__((used)) static HRESULT AntiMonikerImpl_Construct(AntiMonikerImpl* This)
{

    TRACE("(%p)\n",This);

    /* Initialize the virtual function table. */
    This->IMoniker_iface.lpVtbl = &VT_AntiMonikerImpl;
    This->IROTData_iface.lpVtbl = &VT_ROTDataImpl;
    This->ref          = 0;
    This->pMarshal     = NULL;

    return S_OK;
}