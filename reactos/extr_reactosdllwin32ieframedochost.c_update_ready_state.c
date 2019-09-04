#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int loading_pos; int position; } ;
struct TYPE_7__ {scalar_t__ doc_state; int /*<<< orphan*/  browser_service; TYPE_1__ travellog; } ;
typedef  scalar_t__ READYSTATE ;
typedef  TYPE_2__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  DISPID_DOCUMENTCOMPLETE ; 
 int /*<<< orphan*/  DISPID_NAVIGATECOMPLETE2 ; 
 scalar_t__ READYSTATE_COMPLETE ; 
 scalar_t__ READYSTATE_LOADING ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  notif_complete (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_doc_state (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void update_ready_state(DocHost *This, READYSTATE ready_state)
{
    if(ready_state > READYSTATE_LOADING && This->travellog.loading_pos != -1) {
        WARN("histupdate not notified\n");
        This->travellog.position = This->travellog.loading_pos;
        This->travellog.loading_pos = -1;
    }

    if(ready_state > READYSTATE_LOADING && This->doc_state <= READYSTATE_LOADING && !This->browser_service /* FIXME */)
        notif_complete(This, DISPID_NAVIGATECOMPLETE2);

    if(ready_state == READYSTATE_COMPLETE && This->doc_state < READYSTATE_COMPLETE) {
        set_doc_state(This, READYSTATE_COMPLETE);
        if(!This->browser_service) /* FIXME: Not fully correct */
            notif_complete(This, DISPID_DOCUMENTCOMPLETE);
    }else {
        set_doc_state(This, ready_state);
    }
}