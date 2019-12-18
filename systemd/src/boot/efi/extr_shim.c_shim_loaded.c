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
struct ShimLock {int dummy; } ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int /*<<< orphan*/  LocateProtocol; } ;
typedef  int /*<<< orphan*/  EFI_GUID ;
typedef  int BOOLEAN ;

/* Variables and functions */
 TYPE_1__* BS ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  shim_lock_guid ; 
 scalar_t__ uefi_call_wrapper (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

BOOLEAN shim_loaded(void) {
        struct ShimLock *shim_lock;

        return uefi_call_wrapper(BS->LocateProtocol, 3, (EFI_GUID*) &shim_lock_guid, NULL, (VOID**) &shim_lock) == EFI_SUCCESS;
}