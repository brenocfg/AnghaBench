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
struct TYPE_2__ {scalar_t__ handover_offset; int /*<<< orphan*/  code32_start; } ;
struct boot_params {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  (* handover_f ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct boot_params*) ;
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ UINTN ;
typedef  int /*<<< orphan*/  EFI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ST ; 

__attribute__((used)) static VOID linux_efi_handover(EFI_HANDLE image, struct boot_params *params) {
        handover_f handover;
        UINTN start = (UINTN)params->hdr.code32_start;

#ifdef __x86_64__
        asm volatile ("cli");
        start += 512;
#endif
        handover = (handover_f)(start + params->hdr.handover_offset);
        handover(image, ST, params);
}