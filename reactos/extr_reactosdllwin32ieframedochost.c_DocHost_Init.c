#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int loading_pos; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/  cps; TYPE_3__ travellog; int /*<<< orphan*/  task_queue; int /*<<< orphan*/  ready_state; int /*<<< orphan*/  const* container_vtbl; int /*<<< orphan*/ * wb; TYPE_2__ IPropertyNotifySink_iface; TYPE_1__ IOleCommandTarget_iface; TYPE_4__ IDocHostUIHandler2_iface; } ;
typedef  int /*<<< orphan*/  IWebBrowser2 ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDocHostContainerVtbl ;
typedef  TYPE_5__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointContainer_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DocHostUIHandler2Vtbl ; 
 int /*<<< orphan*/  DocHost_ClientSite_Init (TYPE_5__*) ; 
 int /*<<< orphan*/  DocHost_Frame_Init (TYPE_5__*) ; 
 int /*<<< orphan*/  IEHTMLWindow_Init (TYPE_5__*) ; 
 int /*<<< orphan*/  NewWindowManager_Init (TYPE_5__*) ; 
 int /*<<< orphan*/  OleCommandTargetVtbl ; 
 int /*<<< orphan*/  PropertyNotifySinkVtbl ; 
 int /*<<< orphan*/  READYSTATE_UNINITIALIZED ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

void DocHost_Init(DocHost *This, IWebBrowser2 *wb, const IDocHostContainerVtbl* container)
{
    This->IDocHostUIHandler2_iface.lpVtbl  = &DocHostUIHandler2Vtbl;
    This->IOleCommandTarget_iface.lpVtbl   = &OleCommandTargetVtbl;
    This->IPropertyNotifySink_iface.lpVtbl = &PropertyNotifySinkVtbl;

    This->wb = wb;
    This->container_vtbl = container;

    This->ready_state = READYSTATE_UNINITIALIZED;
    list_init(&This->task_queue);

    This->travellog.loading_pos = -1;

    DocHost_ClientSite_Init(This);
    DocHost_Frame_Init(This);

    ConnectionPointContainer_Init(&This->cps, (IUnknown*)wb);
    IEHTMLWindow_Init(This);
    NewWindowManager_Init(This);
}