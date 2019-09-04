#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* DebugInfo; } ;
struct handle_wrapper {TYPE_2__ lock; int /*<<< orphan*/ * hglobal; scalar_t__ delete_on_release; int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {scalar_t__* Spare; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_2__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct handle_wrapper*) ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_release(struct handle_wrapper *handle)
{
    ULONG ref = InterlockedDecrement(&handle->ref);

    if (!ref)
    {
        if (handle->delete_on_release)
        {
            GlobalFree(handle->hglobal);
            handle->hglobal = NULL;
        }

        handle->lock.DebugInfo->Spare[0] = 0;
        DeleteCriticalSection(&handle->lock);
        HeapFree(GetProcessHeap(), 0, handle);
    }
}