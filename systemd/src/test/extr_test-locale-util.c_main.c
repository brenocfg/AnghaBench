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
 int /*<<< orphan*/  dump_special_glyphs () ; 
 int /*<<< orphan*/  test_get_locales () ; 
 int /*<<< orphan*/  test_keymaps () ; 
 int /*<<< orphan*/  test_locale_is_valid () ; 

int main(int argc, char *argv[]) {
        test_get_locales();
        test_locale_is_valid();
        test_keymaps();

        dump_special_glyphs();

        return 0;
}