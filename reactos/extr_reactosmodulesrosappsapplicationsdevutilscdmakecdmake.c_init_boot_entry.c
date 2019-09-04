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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {int boot_id; char* bootimage; int /*<<< orphan*/  load_segment; int /*<<< orphan*/  boot_emu_type; } ;
typedef  TYPE_1__* PBOOT_ENTRY ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
init_boot_entry(PBOOT_ENTRY boot_entry,
                BYTE boot_emu_type, WORD load_segment,
                char* bootimage)
{
    boot_entry->boot_id       = 0x88;           // Bootable entry
    boot_entry->boot_emu_type = boot_emu_type;  // 0: No emulation, etc...
    boot_entry->load_segment  = load_segment;   // If 0 then use default 0x07C0

    boot_entry->bootimage[0]  = '\0';
    strncpy(boot_entry->bootimage, bootimage, sizeof(boot_entry->bootimage));
    boot_entry->bootimage[sizeof(boot_entry->bootimage)-1] = '\0';
}