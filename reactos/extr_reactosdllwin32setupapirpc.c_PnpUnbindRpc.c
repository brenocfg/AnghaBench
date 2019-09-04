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
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/ * RPC_BINDING_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RpcBindingFree (int /*<<< orphan*/ *) ; 

RPC_STATUS
PnpUnbindRpc(RPC_BINDING_HANDLE *BindingHandle)
{
    if (BindingHandle != NULL)
    {
        RpcBindingFree(*BindingHandle);
        *BindingHandle = NULL;
    }

    return RPC_S_OK;
}