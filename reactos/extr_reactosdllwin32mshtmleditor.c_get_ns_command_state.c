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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsICommandParams ;
typedef  int /*<<< orphan*/  nsICommandManager ;
struct TYPE_9__ {TYPE_2__* doc; scalar_t__ webbrowser; } ;
struct TYPE_8__ {int /*<<< orphan*/  nswindow; } ;
struct TYPE_6__ {TYPE_3__* window; } ;
struct TYPE_7__ {TYPE_1__ basedoc; } ;
typedef  TYPE_4__ NSContainer ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IID_nsICommandManager ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 int /*<<< orphan*/  get_nsinterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsICommandManager_GetCommandState (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsICommandManager_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static nsresult get_ns_command_state(NSContainer *This, const char *cmd, nsICommandParams *nsparam)
{
    nsICommandManager *cmdmgr;
    nsresult nsres;

    nsres = get_nsinterface((nsISupports*)This->webbrowser, &IID_nsICommandManager, (void**)&cmdmgr);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsICommandManager: %08x\n", nsres);
        return nsres;
    }

    nsres = nsICommandManager_GetCommandState(cmdmgr, cmd, This->doc->basedoc.window->nswindow, nsparam);
    if(NS_FAILED(nsres))
        ERR("GetCommandState(%s) failed: %08x\n", debugstr_a(cmd), nsres);

    nsICommandManager_Release(cmdmgr);
    return nsres;
}