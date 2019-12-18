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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IOleCommandTarget_iface; } ;
typedef  TYPE_1__ IOleCommandTargetImpl ;
typedef  TYPE_2__ IOleCommandTarget ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IOleCommandTargetImpl_Vtbl ; 

__attribute__((used)) static IOleCommandTarget* IOleCommandTargetImpl_Construct(void)
{
    IOleCommandTargetImpl *obj;

    obj = HeapAlloc(GetProcessHeap(), 0, sizeof(*obj));
    obj->IOleCommandTarget_iface.lpVtbl = &IOleCommandTargetImpl_Vtbl;
    obj->ref = 1;

    return &obj->IOleCommandTarget_iface;
}