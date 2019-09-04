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
struct TYPE_6__ {int ref; int /*<<< orphan*/ * pObject; TYPE_1__ IMoniker_iface; } ;
typedef  TYPE_2__ PointerMonikerImpl ;
typedef  int /*<<< orphan*/  IUnknown ;

/* Variables and functions */
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  VT_PointerMonikerImpl ; 

__attribute__((used)) static void PointerMonikerImpl_Construct(PointerMonikerImpl* This, IUnknown *punk)
{
    TRACE("(%p)\n",This);

    /* Initialize the virtual function table. */
    This->IMoniker_iface.lpVtbl = &VT_PointerMonikerImpl;
    This->ref = 1;
    if (punk)
        IUnknown_AddRef(punk);
    This->pObject      = punk;
}