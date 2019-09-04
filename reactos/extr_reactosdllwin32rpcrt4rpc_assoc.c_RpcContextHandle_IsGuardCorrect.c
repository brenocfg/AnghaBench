#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* ctx_guard; } ;
typedef  TYPE_1__ RpcContextHandle ;
typedef  scalar_t__ NDR_SCONTEXT ;
typedef  int BOOL ;

/* Variables and functions */

BOOL RpcContextHandle_IsGuardCorrect(NDR_SCONTEXT SContext, void *CtxGuard)
{
    RpcContextHandle *context_handle = (RpcContextHandle *)SContext;
    return context_handle->ctx_guard == CtxGuard;
}