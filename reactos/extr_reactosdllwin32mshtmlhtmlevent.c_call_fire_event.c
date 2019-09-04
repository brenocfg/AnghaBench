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
typedef  int /*<<< orphan*/  eventid_t ;
struct TYPE_6__ {int /*<<< orphan*/  nsnode; int /*<<< orphan*/  doc; TYPE_1__* vtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fire_event ) (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
typedef  TYPE_2__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fire_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*) ; 

HRESULT call_fire_event(HTMLDOMNode *node, eventid_t eid)
{
    HRESULT hres;

    if(node->vtbl->fire_event) {
        BOOL handled = FALSE;

        hres = node->vtbl->fire_event(node, eid, &handled);
        if(handled)
            return hres;
    }

    fire_event(node->doc, eid, TRUE, node->nsnode, NULL, NULL);
    return S_OK;
}