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
struct TYPE_3__ {int /*<<< orphan*/  ReleaseFromReadAhead; int /*<<< orphan*/  AcquireForReadAhead; int /*<<< orphan*/  ReleaseFromLazyWrite; int /*<<< orphan*/  AcquireForLazyWrite; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  CACHE_MANAGER_CALLBACKS ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  acquire_for_lazy_write ; 
 int /*<<< orphan*/  acquire_for_read_ahead ; 
 TYPE_1__* cache_callbacks ; 
 int /*<<< orphan*/  release_from_lazy_write ; 
 int /*<<< orphan*/  release_from_read_ahead ; 

NTSTATUS init_cache() {
    cache_callbacks = ExAllocatePoolWithTag(NonPagedPool, sizeof(CACHE_MANAGER_CALLBACKS), ALLOC_TAG);
    if (!cache_callbacks) {
        ERR("out of memory\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    cache_callbacks->AcquireForLazyWrite = acquire_for_lazy_write;
    cache_callbacks->ReleaseFromLazyWrite = release_from_lazy_write;
    cache_callbacks->AcquireForReadAhead = acquire_for_read_ahead;
    cache_callbacks->ReleaseFromReadAhead = release_from_read_ahead;

    return STATUS_SUCCESS;
}