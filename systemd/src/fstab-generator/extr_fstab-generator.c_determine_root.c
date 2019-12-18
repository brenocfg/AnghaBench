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
 int /*<<< orphan*/  arg_root_hash ; 
 scalar_t__ arg_root_what ; 
 int /*<<< orphan*/  log_info (char*,scalar_t__) ; 
 int log_oom () ; 
 scalar_t__ strdup (char*) ; 

__attribute__((used)) static int determine_root(void) {
        /* If we have a root hash but no root device then Verity is used, and we use the "root" DM device as root. */

        if (arg_root_what)
                return 0;

        if (!arg_root_hash)
                return 0;

        arg_root_what = strdup("/dev/mapper/root");
        if (!arg_root_what)
                return log_oom();

        log_info("Using verity root device %s.", arg_root_what);

        return 1;
}