#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ log; scalar_t__ length; } ;
struct TYPE_8__ {scalar_t__ url; TYPE_1__ travellog; int /*<<< orphan*/  cps; scalar_t__ shell_ui_helper; } ;
typedef  TYPE_2__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointContainer_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DocHost_ClientSite_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  IShellUIHelper2_Release (scalar_t__) ; 
 int /*<<< orphan*/  abort_dochost_tasks (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_travellog_entry (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (scalar_t__) ; 
 int /*<<< orphan*/  release_dochost_client (TYPE_2__*) ; 

void DocHost_Release(DocHost *This)
{
    if(This->shell_ui_helper)
        IShellUIHelper2_Release(This->shell_ui_helper);

    abort_dochost_tasks(This, NULL);
    release_dochost_client(This);
    DocHost_ClientSite_Release(This);

    ConnectionPointContainer_Destroy(&This->cps);

    while(This->travellog.length)
        free_travellog_entry(This->travellog.log + --This->travellog.length);
    heap_free(This->travellog.log);

    heap_free(This->url);
}