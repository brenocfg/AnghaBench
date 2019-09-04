#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* data; } ;
struct TYPE_14__ {TYPE_5__* doc; } ;
struct TYPE_11__ {TYPE_7__ dispex; } ;
struct TYPE_12__ {TYPE_3__ event_target; } ;
struct TYPE_13__ {TYPE_4__ node; } ;
struct TYPE_10__ {TYPE_1__* vtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* bind_event ) (TYPE_7__*,int) ;} ;
typedef  TYPE_6__ HTMLInnerWindow ;
typedef  int /*<<< orphan*/  DispatchEx ;

/* Variables and functions */
 TYPE_6__* impl_from_DispatchEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int) ; 

__attribute__((used)) static void HTMLWindow_bind_event(DispatchEx *dispex, int eid)
{
    HTMLInnerWindow *This = impl_from_DispatchEx(dispex);
    This->doc->node.event_target.dispex.data->vtbl->bind_event(&This->doc->node.event_target.dispex, eid);
}