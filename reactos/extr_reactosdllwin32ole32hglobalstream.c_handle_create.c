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
struct handle_wrapper {int ref; TYPE_2__ lock; int /*<<< orphan*/  delete_on_release; int /*<<< orphan*/  size; int /*<<< orphan*/  hglobal; } ;
struct TYPE_3__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GlobalSize (int /*<<< orphan*/ ) ; 
 struct handle_wrapper* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_2__*) ; 

__attribute__((used)) static struct handle_wrapper *handle_create(HGLOBAL hglobal, BOOL delete_on_release)
{
    struct handle_wrapper *handle;

    handle = HeapAlloc(GetProcessHeap(), 0, sizeof(*handle));
    if (handle)
    {
        handle->ref = 1;
        handle->hglobal = hglobal;
        handle->size = GlobalSize(hglobal);
        handle->delete_on_release = delete_on_release;
        InitializeCriticalSection(&handle->lock);
        handle->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": handle_wrapper.lock");
    }
    return handle;
}