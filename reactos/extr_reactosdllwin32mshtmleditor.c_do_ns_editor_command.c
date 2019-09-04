#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
struct TYPE_3__ {int /*<<< orphan*/  editor_controller; } ;
typedef  TYPE_1__ NSContainer ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 int /*<<< orphan*/  nsIController_DoCommand (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void do_ns_editor_command(NSContainer *This, const char *cmd)
{
    nsresult nsres;

    if(!This->editor_controller)
        return;

    nsres = nsIController_DoCommand(This->editor_controller, cmd);
    if(NS_FAILED(nsres))
        ERR("DoCommand(%s) failed: %08x\n", debugstr_a(cmd), nsres);
}