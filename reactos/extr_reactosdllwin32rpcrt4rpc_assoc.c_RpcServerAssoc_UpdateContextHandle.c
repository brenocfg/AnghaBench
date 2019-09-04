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
struct TYPE_6__ {int /*<<< orphan*/  cs; } ;
struct TYPE_5__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  rundown_routine; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ RpcContextHandle ;
typedef  TYPE_2__ RpcAssoc ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  scalar_t__ NDR_SCONTEXT ;
typedef  int /*<<< orphan*/  NDR_RUNDOWN ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RpcContextHandle_IsGuardCorrect (scalar_t__,void*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UuidCreate (int /*<<< orphan*/ *) ; 
 scalar_t__ UuidIsNil (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 

RPC_STATUS RpcServerAssoc_UpdateContextHandle(RpcAssoc *assoc,
                                              NDR_SCONTEXT SContext,
                                              void *CtxGuard,
                                              NDR_RUNDOWN rundown_routine)
{
    RpcContextHandle *context_handle = (RpcContextHandle *)SContext;
    RPC_STATUS status;

    if (!RpcContextHandle_IsGuardCorrect((NDR_SCONTEXT)context_handle, CtxGuard))
        return ERROR_INVALID_HANDLE;

    EnterCriticalSection(&assoc->cs);
    if (UuidIsNil(&context_handle->uuid, &status))
    {
        /* add a ref for the data being valid */
        context_handle->refs++;
        UuidCreate(&context_handle->uuid);
        context_handle->rundown_routine = rundown_routine;
        TRACE("allocated uuid %s for context handle %p\n",
              debugstr_guid(&context_handle->uuid), context_handle);
    }
    LeaveCriticalSection(&assoc->cs);

    return RPC_S_OK;
}