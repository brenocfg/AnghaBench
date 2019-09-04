#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  event_target_t ;
struct TYPE_9__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_10__ {TYPE_2__ event_target; TYPE_1__* doc; } ;
struct TYPE_11__ {TYPE_3__ node; } ;
struct TYPE_12__ {TYPE_4__ element; } ;
struct TYPE_13__ {TYPE_5__ textcont; } ;
struct TYPE_8__ {int /*<<< orphan*/ * body_event_target; } ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  TYPE_6__ HTMLBodyElement ;

/* Variables and functions */
 TYPE_6__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static event_target_t **HTMLBodyElement_get_event_target_ptr(HTMLDOMNode *iface)
{
    HTMLBodyElement *This = impl_from_HTMLDOMNode(iface);

    return This->textcont.element.node.doc
        ? &This->textcont.element.node.doc->body_event_target
        : &This->textcont.element.node.event_target.ptr;
}