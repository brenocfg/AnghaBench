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

/* Variables and functions */
 int /*<<< orphan*/  EFI_VENDOR_LOADER ; 
 int ENOENT ; 
 int efi_get_variable_string (int /*<<< orphan*/ ,char const*,char**) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,char const*) ; 

__attribute__((used)) static void read_loader_efi_var(const char *name, char **var) {
        int r;

        r = efi_get_variable_string(EFI_VENDOR_LOADER, name, var);
        if (r < 0 && r != -ENOENT)
                log_warning_errno(r, "Failed to read EFI variable %s: %m", name);
}