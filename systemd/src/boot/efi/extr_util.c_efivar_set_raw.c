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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINTN ;
typedef  int UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/  SetVariable; } ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_GUID ;
typedef  int /*<<< orphan*/  CHAR16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int EFI_VARIABLE_BOOTSERVICE_ACCESS ; 
 int EFI_VARIABLE_NON_VOLATILE ; 
 int EFI_VARIABLE_RUNTIME_ACCESS ; 
 TYPE_1__* RT ; 
 int /*<<< orphan*/  uefi_call_wrapper (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

EFI_STATUS efivar_set_raw(const EFI_GUID *vendor, const CHAR16 *name, const VOID *buf, UINTN size, BOOLEAN persistent) {
        UINT32 flags;

        flags = EFI_VARIABLE_BOOTSERVICE_ACCESS|EFI_VARIABLE_RUNTIME_ACCESS;
        if (persistent)
                flags |= EFI_VARIABLE_NON_VOLATILE;

        return uefi_call_wrapper(RT->SetVariable, 5, (CHAR16*) name, (EFI_GUID *)vendor, flags, size, (VOID*) buf);
}