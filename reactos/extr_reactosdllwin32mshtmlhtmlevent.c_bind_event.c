#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  eventid_t ;
struct TYPE_10__ {TYPE_2__* data; } ;
struct TYPE_9__ {TYPE_4__ dispex; } ;
struct TYPE_8__ {TYPE_1__* vtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* bind_event ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ EventTarget ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bind_event(EventTarget *event_target, eventid_t eid)
{
    if(event_target->dispex.data->vtbl->bind_event)
        event_target->dispex.data->vtbl->bind_event(&event_target->dispex, eid);
    else
        FIXME("Unsupported event binding on target %p\n", event_target);
}