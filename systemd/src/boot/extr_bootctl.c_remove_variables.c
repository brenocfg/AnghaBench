#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int efi_remove_boot_option (int /*<<< orphan*/ ) ; 
 int find_slot (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_efi_boot () ; 
 int remove_from_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_variables(sd_id128_t uuid, const char *path, bool in_order) {
        uint16_t slot;
        int r;

        if (!is_efi_boot())
                return 0;

        r = find_slot(uuid, path, &slot);
        if (r != 1)
                return 0;

        r = efi_remove_boot_option(slot);
        if (r < 0)
                return r;

        if (in_order)
                return remove_from_order(slot);

        return 0;
}