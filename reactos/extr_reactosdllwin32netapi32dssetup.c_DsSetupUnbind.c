#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ RPC_STATUS ;

/* Variables and functions */
 scalar_t__ RpcBindingFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static
void
DsSetupUnbind(
    handle_t hBinding)
{
    RPC_STATUS status;

    TRACE("DsSetupUnbind()\n");

    status = RpcBindingFree(&hBinding);
    if (status)
    {
        TRACE("RpcBindingFree returned 0x%x\n", status);
    }
}