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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  assert (int) ; 
 int log_tests_skipped (char*) ; 
 int test_acpi_fpdt () ; 
 int test_boot_timestamps () ; 
 int test_efi_loader () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char* argv[]) {
        int p, q, r;

        test_setup_logging(LOG_DEBUG);

        p = test_acpi_fpdt();
        assert(p >= 0);
        q = test_efi_loader();
        assert(q >= 0);
        r = test_boot_timestamps();
        assert(r >= 0);

        if (p == 0 && q == 0 && r == 0)
                return log_tests_skipped("access to firmware variables not possible");

        return EXIT_SUCCESS;
}