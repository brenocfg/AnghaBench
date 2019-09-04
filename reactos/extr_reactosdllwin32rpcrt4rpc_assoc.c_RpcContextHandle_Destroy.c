#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rw_lock; scalar_t__ user_context; int /*<<< orphan*/  (* rundown_routine ) (scalar_t__) ;} ;
typedef  TYPE_1__ RpcContextHandle ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlDeleteResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void RpcContextHandle_Destroy(RpcContextHandle *context_handle)
{
    TRACE("freeing %p\n", context_handle);

    if (context_handle->user_context && context_handle->rundown_routine)
    {
        TRACE("calling rundown routine %p with user context %p\n",
              context_handle->rundown_routine, context_handle->user_context);
        context_handle->rundown_routine(context_handle->user_context);
    }

    RtlDeleteResource(&context_handle->rw_lock);

    HeapFree(GetProcessHeap(), 0, context_handle);
}