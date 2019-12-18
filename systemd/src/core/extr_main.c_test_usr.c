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
 scalar_t__ dir_is_empty (char*) ; 
 int /*<<< orphan*/  log_warning (char*) ; 

__attribute__((used)) static void test_usr(void) {

        /* Check that /usr is either on the same file system as / or mounted already. */

        if (dir_is_empty("/usr") <= 0)
                return;

        log_warning("/usr appears to be on its own filesystem and is not already mounted. This is not a supported setup. "
                    "Some things will probably break (sometimes even silently) in mysterious ways. "
                    "Consult http://freedesktop.org/wiki/Software/systemd/separate-usr-is-broken for more information.");
}