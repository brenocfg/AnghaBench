#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  event_target_t ;
struct TYPE_7__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_9__ {TYPE_2__ event_target; TYPE_1__* vtbl; } ;
struct TYPE_8__ {TYPE_4__ node; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** (* get_event_target_ptr ) (TYPE_4__*) ;} ;
typedef  TYPE_3__ HTMLElement ;
typedef  int /*<<< orphan*/  DispatchEx ;

/* Variables and functions */
 TYPE_3__* impl_from_DispatchEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** stub1 (TYPE_4__*) ; 

__attribute__((used)) static event_target_t **HTMLElement_get_event_target_ptr(DispatchEx *dispex)
{
    HTMLElement *This = impl_from_DispatchEx(dispex);
    return This->node.vtbl->get_event_target_ptr
        ? This->node.vtbl->get_event_target_ptr(&This->node)
        : &This->node.event_target.ptr;
}