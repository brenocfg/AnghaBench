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
typedef  int /*<<< orphan*/ * handle_t ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 scalar_t__ RpcBindingFromStringBindingW (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RpcStringBindingComposeW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RpcStringFreeW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static
RPC_STATUS
DsSetupBind(
    LPWSTR lpServerName,
    handle_t *hBinding)
{
    LPWSTR pszStringBinding;
    RPC_STATUS status;

    TRACE("DsSetupBind() called\n");

    *hBinding = NULL;

    status = RpcStringBindingComposeW(NULL,
                                      L"ncacn_np",
                                      lpServerName,
                                      L"\\pipe\\lsarpc",
                                      NULL,
                                      &pszStringBinding);
    if (status)
    {
        TRACE("RpcStringBindingCompose returned 0x%x\n", status);
        return status;
    }

    /* Set the binding handle that will be used to bind to the server. */
    status = RpcBindingFromStringBindingW(pszStringBinding,
                                          hBinding);
    if (status)
    {
        TRACE("RpcBindingFromStringBinding returned 0x%x\n", status);
    }

    status = RpcStringFreeW(&pszStringBinding);
    if (status)
    {
        TRACE("RpcStringFree returned 0x%x\n", status);
    }

    return status;
}